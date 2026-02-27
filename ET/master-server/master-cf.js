export class MasterServer {
	constructor(state) {
		this.state = state;
	}

	async fetch(request) {
		if (request.headers.get('Upgrade') !== 'websocket') {
			return new Response('Expected WebSocket', { status: 426 });
		}

		const pair = new WebSocketPair();
		const [client, server] = Object.values(pair);

		const id = crypto.randomUUID().slice(0, 8);
		this.state.acceptWebSocket(server, ['peer-' + id]);
		server.serializeAttachment({ id, server: null });
		server.send(JSON.stringify({ type: 'id', id }));

		return new Response(null, { status: 101, webSocket: client });
	}

	async webSocketMessage(ws, message) {
		const att = ws.deserializeAttachment();
		let msg;
		try { msg = JSON.parse(message); } catch { return; }

		switch (msg.type) {
		case 'heartbeat':
			att.server = msg.info || {};
			ws.serializeAttachment(att);
			break;

		case 'quit':
			att.server = null;
			ws.serializeAttachment(att);
			break;

		case 'getservers': {
			const list = [];
			for (const peer of this.state.getWebSockets()) {
				const pa = peer.deserializeAttachment();
				if (!pa || !pa.server) continue;
				// Build Quake info string: \key\value\key\value
				let info = '\\id\\' + pa.id;
				for (const [k, v] of Object.entries(pa.server)) {
					info += '\\' + k + '\\' + v;
				}
				list.push(info);
			}
			ws.send(JSON.stringify({ type: 'servers', list }));
			break;
		}

		case 'relay': {
			const targets = this.state.getWebSockets('peer-' + msg.target);
			if (!targets.length) break;
			targets[0].send(JSON.stringify({
				type: 'relay', from: att.id, data: msg.data
			}));
			break;
		}

		case 'offer':
		case 'answer':
		case 'ice': {
			const targets = this.state.getWebSockets('peer-' + msg.target);
			if (!targets.length) break;
			targets[0].send(JSON.stringify({
				type: msg.type, from: att.id, sdp: msg.sdp, candidate: msg.candidate
			}));
			break;
		}
		}
	}

	async webSocketClose(ws) { ws.close(); }
	async webSocketError(ws) { ws.close(); }
}

export default {
	async fetch(request, env) {
		const id = env.MASTER.idFromName('master');
		return env.MASTER.get(id).fetch(request);
	}
};

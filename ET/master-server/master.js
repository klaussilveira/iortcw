#!/usr/bin/env node
'use strict';

const { WebSocketServer } = require('ws');

const PORT = parseInt(process.env.PORT || '27950', 10);
const wss = new WebSocketServer({ port: PORT });

let nextId = 1;
const peers = new Map();

wss.on('listening', () => {
	console.log('Master/signaling server on ws://0.0.0.0:' + PORT);
});

wss.on('connection', (ws) => {
	const id = String(nextId++);
	peers.set(id, { ws, server: null });
	send(ws, { type: 'id', id });
	console.log('[' + id + '] connected');

	ws.on('message', (raw) => {
		let msg;
		try { msg = JSON.parse(raw); } catch { return; }

		switch (msg.type) {
		case 'heartbeat':
			peers.get(id).server = msg.info || {};
			console.log('[' + id + '] heartbeat: ' + JSON.stringify(msg.info));
			break;

		case 'quit':
			peers.get(id).server = null;
			console.log('[' + id + '] unregistered');
			break;

		case 'getservers': {
			const list = [];
			for (const [sid, peer] of peers) {
				if (!peer.server) continue;
				// Build Quake info string: \key\value\key\value
				let info = '\\id\\' + sid;
				for (const [k, v] of Object.entries(peer.server)) {
					info += '\\' + k + '\\' + v;
				}
				list.push(info);
			}
			send(ws, { type: 'servers', list });
			break;
		}

		case 'relay': {
			const target = peers.get(msg.target);
			if (!target) break;
			send(target.ws, { type: 'relay', from: id, data: msg.data });
			break;
		}

		case 'offer':
		case 'answer':
		case 'ice': {
			const target = peers.get(msg.target);
			if (!target) break;
			send(target.ws, { type: msg.type, from: id, sdp: msg.sdp, candidate: msg.candidate });
			break;
		}
		}
	});

	ws.on('close', () => {
		peers.delete(id);
		console.log('[' + id + '] disconnected');
	});

	ws.on('error', (err) => {
		console.error('[' + id + '] error: ' + err.message);
	});
});

function send(ws, obj) {
	if (ws.readyState === 1) ws.send(JSON.stringify(obj));
}

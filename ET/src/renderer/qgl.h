/*
===========================================================================

Wolfenstein: Enemy Territory GPL Source Code
Copyright (C) 1999-2010 id Software LLC, a ZeniMax Media company.

This file is part of the Wolfenstein: Enemy Territory GPL Source Code (Wolf ET Source Code).

Wolf ET Source Code is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Wolf ET Source Code is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Wolf ET Source Code.  If not, see <http://www.gnu.org/licenses/>.

In addition, the Wolf: ET Source Code is also subject to certain additional terms. You should have received a copy of these additional terms immediately following the terms and conditions of the GNU General Public License which accompanied the Wolf ET Source Code.  If not, please request a copy in writing from id Software at the address below.

If you have questions concerning this license or the applicable additional terms, you may contact in writing id Software LLC, c/o ZeniMax Media Inc., Suite 120, Rockville, Maryland 20850 USA.

===========================================================================
*/

/*
** QGL.H
*/

#ifndef __QGL_H__
#define __QGL_H__

#ifdef USE_LOCAL_HEADERS
#	include "SDL_opengl.h"
#else
#	include <SDL_opengl.h>
#endif

#ifndef APIENTRY
#define APIENTRY
#endif
#ifndef WINAPI
#define WINAPI
#endif


//===========================================================================

/*
** multitexture extension definitions
*/
#define GL_ACTIVE_TEXTURE_ARB               0x84E0
#define GL_CLIENT_ACTIVE_TEXTURE_ARB        0x84E1
#define GL_MAX_ACTIVE_TEXTURES_ARB          0x84E2

#define GL_TEXTURE0_ARB                     0x84C0
#define GL_TEXTURE1_ARB                     0x84C1
#define GL_TEXTURE2_ARB                     0x84C2
#define GL_TEXTURE3_ARB                     0x84C3


// GL_ATI_pn_triangles
#ifndef GL_ATI_pn_triangles
#define GL_ATI_pn_triangles 1

#define GL_PN_TRIANGLES_ATI                         0x6090
#define GL_MAX_PN_TRIANGLES_TESSELATION_LEVEL_ATI   0x6091
#define GL_PN_TRIANGLES_POINT_MODE_ATI              0x6092
#define GL_PN_TRIANGLES_NORMAL_MODE_ATI             0x6093
#define GL_PN_TRIANGLES_TESSELATION_LEVEL_ATI       0x6094
#define GL_PN_TRIANGLES_POINT_MODE_LINEAR_ATI       0x6095
#define GL_PN_TRIANGLES_POINT_MODE_CUBIC_ATI        0x6096
#define GL_PN_TRIANGLES_NORMAL_MODE_LINEAR_ATI      0x6097
#define GL_PN_TRIANGLES_NORMAL_MODE_QUADRATIC_ATI   0x6098

typedef void ( APIENTRY * PFNGLPNTRIANGLESIATIPROC )( GLenum pname, GLint param );
typedef void ( APIENTRY * PFNGLPNTRIANGLESFATIPROC )( GLenum pname, GLfloat param );
#endif

// for NV fog distance
#ifndef GL_NV_fog_distance
#define GL_FOG_DISTANCE_MODE_NV           0x855A
#define GL_EYE_RADIAL_NV                  0x855B
#define GL_EYE_PLANE_ABSOLUTE_NV          0x855C
/* reuse GL_EYE_PLANE */
#endif

// S3TC compression constants
#define GL_RGB_S3TC                         0x83A0
#define GL_RGB4_S3TC                        0x83A1

// GL_EXT_texture_compression_s3tc constants
#define GL_COMPRESSED_RGB_S3TC_DXT1_EXT                   0x83F0
#define GL_COMPRESSED_RGBA_S3TC_DXT1_EXT                  0x83F1
#define GL_COMPRESSED_RGBA_S3TC_DXT3_EXT                  0x83F2
#define GL_COMPRESSED_RGBA_S3TC_DXT5_EXT                  0x83F3

// GL_EXT_texture_filter_anisotropic constants
#ifndef GL_EXT_texture_filter_anisotropic
#define GL_TEXTURE_MAX_ANISOTROPY_EXT     0x84FE
#define GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT 0x84FF
#endif

// GL_SGIS_generate_mipmap
#ifndef GL_SGIS_generate_mipmap
#define GL_GENERATE_MIPMAP_SGIS           0x8191
#define GL_GENERATE_MIPMAP_HINT_SGIS      0x8192
#endif

// extensions will be function pointers on all platforms

extern void ( APIENTRY * qglMultiTexCoord2fARB )( GLenum texture, GLfloat s, GLfloat t );
extern void ( APIENTRY * qglActiveTextureARB )( GLenum texture );
extern void ( APIENTRY * qglClientActiveTextureARB )( GLenum texture );

extern void ( APIENTRY * qglLockArraysEXT )( GLint, GLint );
extern void ( APIENTRY * qglUnlockArraysEXT )( void );

//----(SA)	added
extern void ( APIENTRY * qglPNTrianglesiATI )( GLenum pname, GLint param );
extern void ( APIENTRY * qglPNTrianglesfATI )( GLenum pname, GLfloat param );
//----(SA)	end

//===========================================================================

// non-windows systems will just redefine qgl* to gl*
#include "qgl_linked.h"

#endif

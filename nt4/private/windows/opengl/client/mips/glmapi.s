
//////////////////////////////////////////////////////////
//     This file was generated by obj\mips\capimips
//             DO NOT MODIFY
//////////////////////////////////////////////////////////

#include "ksmips.h"
#include "dispindx.h"

    .extern dwTlsOffset 4

// Do an indirect jump through the OpenGL function dispatch table.
// This macro must leave the TEB pointer in t7

#define MAKEOPENGLAPI(Name)                 \
        .text;                              \
        .align  2;                          \
        .globl  Name;                       \
        .ent    Name, 0;                    \
Name:;                                      \
        .frame  sp, 0, ra;                  \
        .prologue 0;                        \
        li      t7, UsPcr;                  \
        lw      t7, PcTeb(t7);              \
        lw      t8, dwTlsOffset;            \
        addu    t8, t7, t8;                 \
        lw      t8, (t8);                   \
        lw      t8, INDEX_##Name*4(t8);     \
        j       t8;                         \
        .end;

// Do an indirect jump through the OpenGL function dispatch table in the TEB.
// This macro must leave the TEB pointer in t7

#define FASTOPENGLAPI(Name)                 \
        .text;                              \
        .align  2;                          \
        .globl  Name;                       \
        .ent    Name, 0;                    \
Name:;                                      \
        .frame  sp, 0, ra;                  \
        .prologue 0;                        \
        li      t7, UsPcr;                  \
        lw      t7, PcTeb(t7);              \
        lw      t8, (TeglDispatchTable+(FASTINDEX_##Name*4))(t7); \
        j       t8;                         \
        .end;

FASTOPENGLAPI( glCallList                )
FASTOPENGLAPI( glCallLists               )
FASTOPENGLAPI( glBegin                   )
FASTOPENGLAPI( glColor3b                 )
FASTOPENGLAPI( glColor3bv                )
FASTOPENGLAPI( glColor3d                 )
FASTOPENGLAPI( glColor3dv                )
FASTOPENGLAPI( glColor3f                 )
FASTOPENGLAPI( glColor3fv                )
FASTOPENGLAPI( glColor3i                 )
FASTOPENGLAPI( glColor3iv                )
FASTOPENGLAPI( glColor3s                 )
FASTOPENGLAPI( glColor3sv                )
FASTOPENGLAPI( glColor3ub                )
FASTOPENGLAPI( glColor3ubv               )
FASTOPENGLAPI( glColor3ui                )
FASTOPENGLAPI( glColor3uiv               )
FASTOPENGLAPI( glColor3us                )
FASTOPENGLAPI( glColor3usv               )
FASTOPENGLAPI( glColor4b                 )
FASTOPENGLAPI( glColor4bv                )
FASTOPENGLAPI( glColor4d                 )
FASTOPENGLAPI( glColor4dv                )
FASTOPENGLAPI( glColor4f                 )
FASTOPENGLAPI( glColor4fv                )
FASTOPENGLAPI( glColor4i                 )
FASTOPENGLAPI( glColor4iv                )
FASTOPENGLAPI( glColor4s                 )
FASTOPENGLAPI( glColor4sv                )
FASTOPENGLAPI( glColor4ub                )
FASTOPENGLAPI( glColor4ubv               )
FASTOPENGLAPI( glColor4ui                )
FASTOPENGLAPI( glColor4uiv               )
FASTOPENGLAPI( glColor4us                )
FASTOPENGLAPI( glColor4usv               )
FASTOPENGLAPI( glEdgeFlag                )
FASTOPENGLAPI( glEdgeFlagv               )
FASTOPENGLAPI( glEnd                     )
FASTOPENGLAPI( glIndexd                  )
FASTOPENGLAPI( glIndexdv                 )
FASTOPENGLAPI( glIndexf                  )
FASTOPENGLAPI( glIndexfv                 )
FASTOPENGLAPI( glIndexi                  )
FASTOPENGLAPI( glIndexiv                 )
FASTOPENGLAPI( glIndexs                  )
FASTOPENGLAPI( glIndexsv                 )
FASTOPENGLAPI( glNormal3b                )
FASTOPENGLAPI( glNormal3bv               )
FASTOPENGLAPI( glNormal3d                )
FASTOPENGLAPI( glNormal3dv               )
FASTOPENGLAPI( glNormal3f                )
FASTOPENGLAPI( glNormal3fv               )
FASTOPENGLAPI( glNormal3i                )
FASTOPENGLAPI( glNormal3iv               )
FASTOPENGLAPI( glNormal3s                )
FASTOPENGLAPI( glNormal3sv               )
FASTOPENGLAPI( glTexCoord1d              )
FASTOPENGLAPI( glTexCoord1dv             )
FASTOPENGLAPI( glTexCoord1f              )
FASTOPENGLAPI( glTexCoord1fv             )
FASTOPENGLAPI( glTexCoord1i              )
FASTOPENGLAPI( glTexCoord1iv             )
FASTOPENGLAPI( glTexCoord1s              )
FASTOPENGLAPI( glTexCoord1sv             )
FASTOPENGLAPI( glTexCoord2d              )
FASTOPENGLAPI( glTexCoord2dv             )
FASTOPENGLAPI( glTexCoord2f              )
FASTOPENGLAPI( glTexCoord2fv             )
FASTOPENGLAPI( glTexCoord2i              )
FASTOPENGLAPI( glTexCoord2iv             )
FASTOPENGLAPI( glTexCoord2s              )
FASTOPENGLAPI( glTexCoord2sv             )
FASTOPENGLAPI( glTexCoord3d              )
FASTOPENGLAPI( glTexCoord3dv             )
FASTOPENGLAPI( glTexCoord3f              )
FASTOPENGLAPI( glTexCoord3fv             )
FASTOPENGLAPI( glTexCoord3i              )
FASTOPENGLAPI( glTexCoord3iv             )
FASTOPENGLAPI( glTexCoord3s              )
FASTOPENGLAPI( glTexCoord3sv             )
FASTOPENGLAPI( glTexCoord4d              )
FASTOPENGLAPI( glTexCoord4dv             )
FASTOPENGLAPI( glTexCoord4f              )
FASTOPENGLAPI( glTexCoord4fv             )
FASTOPENGLAPI( glTexCoord4i              )
FASTOPENGLAPI( glTexCoord4iv             )
FASTOPENGLAPI( glTexCoord4s              )
FASTOPENGLAPI( glTexCoord4sv             )
FASTOPENGLAPI( glVertex2d                )
FASTOPENGLAPI( glVertex2dv               )
FASTOPENGLAPI( glVertex2f                )
FASTOPENGLAPI( glVertex2fv               )
FASTOPENGLAPI( glVertex2i                )
FASTOPENGLAPI( glVertex2iv               )
FASTOPENGLAPI( glVertex2s                )
FASTOPENGLAPI( glVertex2sv               )
FASTOPENGLAPI( glVertex3d                )
FASTOPENGLAPI( glVertex3dv               )
FASTOPENGLAPI( glVertex3f                )
FASTOPENGLAPI( glVertex3fv               )
FASTOPENGLAPI( glVertex3i                )
FASTOPENGLAPI( glVertex3iv               )
FASTOPENGLAPI( glVertex3s                )
FASTOPENGLAPI( glVertex3sv               )
FASTOPENGLAPI( glVertex4d                )
FASTOPENGLAPI( glVertex4dv               )
FASTOPENGLAPI( glVertex4f                )
FASTOPENGLAPI( glVertex4fv               )
FASTOPENGLAPI( glVertex4i                )
FASTOPENGLAPI( glVertex4iv               )
FASTOPENGLAPI( glVertex4s                )
FASTOPENGLAPI( glVertex4sv               )
FASTOPENGLAPI( glMaterialf               )
FASTOPENGLAPI( glMaterialfv              )
FASTOPENGLAPI( glMateriali               )
FASTOPENGLAPI( glMaterialiv              )
FASTOPENGLAPI( glDisable                 )
FASTOPENGLAPI( glEnable                  )
FASTOPENGLAPI( glPopAttrib               )
FASTOPENGLAPI( glPushAttrib              )
FASTOPENGLAPI( glEvalCoord1d             )
FASTOPENGLAPI( glEvalCoord1dv            )
FASTOPENGLAPI( glEvalCoord1f             )
FASTOPENGLAPI( glEvalCoord1fv            )
FASTOPENGLAPI( glEvalCoord2d             )
FASTOPENGLAPI( glEvalCoord2dv            )
FASTOPENGLAPI( glEvalCoord2f             )
FASTOPENGLAPI( glEvalCoord2fv            )
FASTOPENGLAPI( glEvalPoint1              )
FASTOPENGLAPI( glEvalPoint2              )
FASTOPENGLAPI( glLoadIdentity            )
FASTOPENGLAPI( glLoadMatrixf             )
FASTOPENGLAPI( glLoadMatrixd             )
FASTOPENGLAPI( glMatrixMode              )
FASTOPENGLAPI( glMultMatrixf             )
FASTOPENGLAPI( glMultMatrixd             )
FASTOPENGLAPI( glPopMatrix               )
FASTOPENGLAPI( glPushMatrix              )
FASTOPENGLAPI( glRotated                 )
FASTOPENGLAPI( glRotatef                 )
FASTOPENGLAPI( glScaled                  )
FASTOPENGLAPI( glScalef                  )
FASTOPENGLAPI( glTranslated              )
FASTOPENGLAPI( glTranslatef              )
FASTOPENGLAPI( glArrayElement            )
FASTOPENGLAPI( glBindTexture             )
FASTOPENGLAPI( glColorPointer            )
FASTOPENGLAPI( glDisableClientState      )
FASTOPENGLAPI( glDrawArrays              )
FASTOPENGLAPI( glDrawElements            )
FASTOPENGLAPI( glEdgeFlagPointer         )
FASTOPENGLAPI( glEnableClientState       )
FASTOPENGLAPI( glIndexPointer            )
FASTOPENGLAPI( glIndexub                 )
FASTOPENGLAPI( glIndexubv                )
FASTOPENGLAPI( glInterleavedArrays       )
FASTOPENGLAPI( glNormalPointer           )
FASTOPENGLAPI( glPolygonOffset           )
FASTOPENGLAPI( glTexCoordPointer         )
FASTOPENGLAPI( glVertexPointer           )
FASTOPENGLAPI( glGetPointerv             )
FASTOPENGLAPI( glPopClientAttrib         )
FASTOPENGLAPI( glPushClientAttrib        )
FASTOPENGLAPI( glColorTableEXT           )
FASTOPENGLAPI( glColorSubTableEXT        )

MAKEOPENGLAPI( glClear                   )
MAKEOPENGLAPI( glClearAccum              )
MAKEOPENGLAPI( glClearIndex              )
MAKEOPENGLAPI( glClearColor              )
MAKEOPENGLAPI( glClearStencil            )
MAKEOPENGLAPI( glClearDepth              )
MAKEOPENGLAPI( glBitmap                  )
MAKEOPENGLAPI( glTexImage1D              )
MAKEOPENGLAPI( glTexImage2D              )
MAKEOPENGLAPI( glCopyPixels              )
MAKEOPENGLAPI( glReadPixels              )
MAKEOPENGLAPI( glDrawPixels              )
MAKEOPENGLAPI( glRectd                   )
MAKEOPENGLAPI( glRectdv                  )
MAKEOPENGLAPI( glRectf                   )
MAKEOPENGLAPI( glRectfv                  )
MAKEOPENGLAPI( glRecti                   )
MAKEOPENGLAPI( glRectiv                  )
MAKEOPENGLAPI( glRects                   )
MAKEOPENGLAPI( glRectsv                  )
MAKEOPENGLAPI( glNewList                 )
MAKEOPENGLAPI( glEndList                 )
MAKEOPENGLAPI( glDeleteLists             )
MAKEOPENGLAPI( glGenLists                )
MAKEOPENGLAPI( glListBase                )
MAKEOPENGLAPI( glRasterPos2d             )
MAKEOPENGLAPI( glRasterPos2dv            )
MAKEOPENGLAPI( glRasterPos2f             )
MAKEOPENGLAPI( glRasterPos2fv            )
MAKEOPENGLAPI( glRasterPos2i             )
MAKEOPENGLAPI( glRasterPos2iv            )
MAKEOPENGLAPI( glRasterPos2s             )
MAKEOPENGLAPI( glRasterPos2sv            )
MAKEOPENGLAPI( glRasterPos3d             )
MAKEOPENGLAPI( glRasterPos3dv            )
MAKEOPENGLAPI( glRasterPos3f             )
MAKEOPENGLAPI( glRasterPos3fv            )
MAKEOPENGLAPI( glRasterPos3i             )
MAKEOPENGLAPI( glRasterPos3iv            )
MAKEOPENGLAPI( glRasterPos3s             )
MAKEOPENGLAPI( glRasterPos3sv            )
MAKEOPENGLAPI( glRasterPos4d             )
MAKEOPENGLAPI( glRasterPos4dv            )
MAKEOPENGLAPI( glRasterPos4f             )
MAKEOPENGLAPI( glRasterPos4fv            )
MAKEOPENGLAPI( glRasterPos4i             )
MAKEOPENGLAPI( glRasterPos4iv            )
MAKEOPENGLAPI( glRasterPos4s             )
MAKEOPENGLAPI( glRasterPos4sv            )
MAKEOPENGLAPI( glClipPlane               )
MAKEOPENGLAPI( glColorMaterial           )
MAKEOPENGLAPI( glCullFace                )
MAKEOPENGLAPI( glFogf                    )
MAKEOPENGLAPI( glFogfv                   )
MAKEOPENGLAPI( glFogi                    )
MAKEOPENGLAPI( glFogiv                   )
MAKEOPENGLAPI( glFrontFace               )
MAKEOPENGLAPI( glHint                    )
MAKEOPENGLAPI( glLightf                  )
MAKEOPENGLAPI( glLightfv                 )
MAKEOPENGLAPI( glLighti                  )
MAKEOPENGLAPI( glLightiv                 )
MAKEOPENGLAPI( glLightModelf             )
MAKEOPENGLAPI( glLightModelfv            )
MAKEOPENGLAPI( glLightModeli             )
MAKEOPENGLAPI( glLightModeliv            )
MAKEOPENGLAPI( glLineStipple             )
MAKEOPENGLAPI( glLineWidth               )
MAKEOPENGLAPI( glPointSize               )
MAKEOPENGLAPI( glPolygonMode             )
MAKEOPENGLAPI( glPolygonStipple          )
MAKEOPENGLAPI( glScissor                 )
MAKEOPENGLAPI( glFinish                  )
MAKEOPENGLAPI( glShadeModel              )
MAKEOPENGLAPI( glTexParameterf           )
MAKEOPENGLAPI( glTexParameterfv          )
MAKEOPENGLAPI( glTexParameteri           )
MAKEOPENGLAPI( glTexParameteriv          )
MAKEOPENGLAPI( glTexEnvf                 )
MAKEOPENGLAPI( glTexEnvfv                )
MAKEOPENGLAPI( glTexEnvi                 )
MAKEOPENGLAPI( glTexEnviv                )
MAKEOPENGLAPI( glTexGend                 )
MAKEOPENGLAPI( glTexGendv                )
MAKEOPENGLAPI( glTexGenf                 )
MAKEOPENGLAPI( glTexGenfv                )
MAKEOPENGLAPI( glTexGeni                 )
MAKEOPENGLAPI( glTexGeniv                )
MAKEOPENGLAPI( glFeedbackBuffer          )
MAKEOPENGLAPI( glSelectBuffer            )
MAKEOPENGLAPI( glRenderMode              )
MAKEOPENGLAPI( glInitNames               )
MAKEOPENGLAPI( glLoadName                )
MAKEOPENGLAPI( glPassThrough             )
MAKEOPENGLAPI( glPopName                 )
MAKEOPENGLAPI( glPushName                )
MAKEOPENGLAPI( glDrawBuffer              )
MAKEOPENGLAPI( glStencilMask             )
MAKEOPENGLAPI( glColorMask               )
MAKEOPENGLAPI( glDepthMask               )
MAKEOPENGLAPI( glIndexMask               )
MAKEOPENGLAPI( glAccum                   )
MAKEOPENGLAPI( glFlush                   )
MAKEOPENGLAPI( glMap1d                   )
MAKEOPENGLAPI( glMap1f                   )
MAKEOPENGLAPI( glMap2d                   )
MAKEOPENGLAPI( glMap2f                   )
MAKEOPENGLAPI( glMapGrid1d               )
MAKEOPENGLAPI( glMapGrid1f               )
MAKEOPENGLAPI( glMapGrid2d               )
MAKEOPENGLAPI( glMapGrid2f               )
MAKEOPENGLAPI( glEvalMesh1               )
MAKEOPENGLAPI( glEvalMesh2               )
MAKEOPENGLAPI( glAlphaFunc               )
MAKEOPENGLAPI( glBlendFunc               )
MAKEOPENGLAPI( glLogicOp                 )
MAKEOPENGLAPI( glStencilFunc             )
MAKEOPENGLAPI( glStencilOp               )
MAKEOPENGLAPI( glDepthFunc               )
MAKEOPENGLAPI( glPixelZoom               )
MAKEOPENGLAPI( glPixelTransferf          )
MAKEOPENGLAPI( glPixelTransferi          )
MAKEOPENGLAPI( glPixelStoref             )
MAKEOPENGLAPI( glPixelStorei             )
MAKEOPENGLAPI( glPixelMapfv              )
MAKEOPENGLAPI( glPixelMapuiv             )
MAKEOPENGLAPI( glPixelMapusv             )
MAKEOPENGLAPI( glReadBuffer              )
MAKEOPENGLAPI( glGetBooleanv             )
MAKEOPENGLAPI( glGetClipPlane            )
MAKEOPENGLAPI( glGetDoublev              )
MAKEOPENGLAPI( glGetError                )
MAKEOPENGLAPI( glGetFloatv               )
MAKEOPENGLAPI( glGetIntegerv             )
MAKEOPENGLAPI( glGetLightfv              )
MAKEOPENGLAPI( glGetLightiv              )
MAKEOPENGLAPI( glGetMapdv                )
MAKEOPENGLAPI( glGetMapfv                )
MAKEOPENGLAPI( glGetMapiv                )
MAKEOPENGLAPI( glGetMaterialfv           )
MAKEOPENGLAPI( glGetMaterialiv           )
MAKEOPENGLAPI( glGetPixelMapfv           )
MAKEOPENGLAPI( glGetPixelMapuiv          )
MAKEOPENGLAPI( glGetPixelMapusv          )
MAKEOPENGLAPI( glGetPolygonStipple       )
MAKEOPENGLAPI( glGetString               )
MAKEOPENGLAPI( glGetTexEnvfv             )
MAKEOPENGLAPI( glGetTexEnviv             )
MAKEOPENGLAPI( glGetTexGendv             )
MAKEOPENGLAPI( glGetTexGenfv             )
MAKEOPENGLAPI( glGetTexGeniv             )
MAKEOPENGLAPI( glGetTexImage             )
MAKEOPENGLAPI( glGetTexParameterfv       )
MAKEOPENGLAPI( glGetTexParameteriv       )
MAKEOPENGLAPI( glGetTexLevelParameterfv  )
MAKEOPENGLAPI( glGetTexLevelParameteriv  )
MAKEOPENGLAPI( glIsEnabled               )
MAKEOPENGLAPI( glIsList                  )
MAKEOPENGLAPI( glDepthRange              )
MAKEOPENGLAPI( glFrustum                 )
MAKEOPENGLAPI( glOrtho                   )
MAKEOPENGLAPI( glViewport                )
MAKEOPENGLAPI( glAreTexturesResident     )
MAKEOPENGLAPI( glCopyTexImage1D          )
MAKEOPENGLAPI( glCopyTexImage2D          )
MAKEOPENGLAPI( glCopyTexSubImage1D       )
MAKEOPENGLAPI( glCopyTexSubImage2D       )
MAKEOPENGLAPI( glDeleteTextures          )
MAKEOPENGLAPI( glGenTextures             )
MAKEOPENGLAPI( glIsTexture               )
MAKEOPENGLAPI( glPrioritizeTextures      )
MAKEOPENGLAPI( glTexSubImage1D           )
MAKEOPENGLAPI( glTexSubImage2D           )
MAKEOPENGLAPI( glGetColorTableEXT        )
MAKEOPENGLAPI( glGetColorTableParameterivEXT )
MAKEOPENGLAPI( glGetColorTableParameterfvEXT )

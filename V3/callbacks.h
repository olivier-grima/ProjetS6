/* Author Yassine El Aissaoui & Olivier Grima
 */

#pragma once

extern void quit(Widget, void *);
extern void initStruct(Donnes *, FILE *);
extern void structOscillateur(Widget,void *);
extern void structStable(Widget,void *);
extern void structVaisseau(Widget,void *);
extern void structMathusalhem(Widget,void *);
extern void randomStruct(Widget,void *);
extern void newDisplay(Donnes *);
extern void scrollCallback(Widget , float , void *);
extern void autoModeNormal(void *, XtIntervalId *id);
extern void CBtogglenormal(Widget,void *);
extern void autoModeVariant(void *, XtIntervalId *id);
extern void CBtogglevariant(Widget,void *);
extern void playNormal(Widget, void *);
extern void playVariant(Widget, void *);
extern void traceDeBase(Widget, int, int, void *);
//extern void structDef(Widget w, void *data);

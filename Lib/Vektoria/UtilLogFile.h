// UtilLogFile.h: 
//
// Enthält Utility FunctionHheaders für ein Logfile
// Nicht Objektorientiert, damit man es einfach global über alle Klassen verwenden kann!
//
// Copyright: Tobias Breiner, Company Vektoria UG (haftungsbeschränkt), Germany
// -----------------------------------------------------------------------

#if !defined(UTL_LOG_H)
#define UTL_LOG_H

#include "..\\VektoriaMath\\HVector.h"
#include "..\\VektoriaMath\\HMat.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "windows.h"
#include <stdio.h>

namespace Vektoria
{



// Anfang und Ende:
void ULInit(LPCSTR szFile); // Initialisiert das Logfile und öffnet es zum schreiben, es ist wichtig, den Pfad mit Suffix anzugeben, z.B.  "C:\\Work\\Log.txt" oder "Log\\Vektoria.log"
void ULFini(); // Finalisiert das Logfile

// An und aus:
void ULOn();// Schaltet Logfile an (Default)
void ULOff(); // Schaltet Lofile aus

// Hilfs-Routinen for die Logfile-Einträge, :
void ULStart(LPCSTR szMsg, bool bOn = true); // Startet das Logfile, schreibt Überschrift und setzt die Logfile-Uhr auf Null Sekunden  
void ULWrite(LPCSTR szMsg); // Schreibt die Meldung szMsg ins Logfile
void ULWriteLn(LPCSTR szMsg); // Schriebt die Meldung szMsg ins Logfile und geht danach in die nächste Zeile
void ULLine(char ch, int iLength); // Erzeugt  einen Unterstrich der Länge iLength mit dem Zeichen ch

// Eintrags-Routinen (können so verwendet werden, wie mit "printf"):
void ULSection(LPCSTR szMsg, ...); // Schreibt eine Überschrift ins Logfile
bool ULCheckFile(LPCSTR szFile, BOOL bReadWrite = false); // Checkt, of das File mit dem Pfad szFile zu öffnen ist, uns schreibt das Ergebnis ins Logfile
void ULOk(LPCSTR szMsg, ...); // Schreibt eine OK-Meldung ins Logfile
void ULInfo(LPCSTR szMsg, ...); // Schreibt eine INFO-Meldung ins Logfile
void ULWarn(LPCSTR szMsg, ...); // Schreibt eine WARN-Meldung ins Logfile
void ULError(LPCSTR szMsg, ...); // Schreibt eine ERROR-Meldung ins Logfile
void ULDebug(LPCSTR szMsg, ...); // Schreibt eine DEBUG-Meldung ins Logfile
void ULVector(LPCSTR szVektor, CHVector v); // Schreibt die 4 Tupelinhalte des homogenen Vektors v ins Logfile, szVektor ist der Name des Vektors
void ULMat(LPCSTR szMat, CHMat m); // Schreibt  die 16 Tupelinhalte der homogenen Matrix m ins Logfile, szMat ist der Name der Matrix

}

#endif 

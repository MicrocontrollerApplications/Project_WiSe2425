# MCON - Semesterprojekt WiSe 24/25
Link zu [MOODLE](https://www.moodle-thu.de).
___
# Beschreibung
Im heutigen Labor werden Sie den Umgang mit einem digitalen Sensor kennenlernen.

Hierzu werden Sie sich mit dem Sensor SHT21 und seiner Funktionsweise vertraut machen, bestehenden Code untersuchen und 
verstehen, sowie selbst Code schreiben, um den Sensor in Betrieb zu nehmen.
Das Datenblatt des Sensors finden Sie 
[hier](https://sensirion.com/media/documents/120BBE4C/63500094/Sensirion_Datasheet_Humidity_Sensor_SHT21.pdf).

Die für Sie relevanten Kapitel im Datenblatt sind:
  - Sensor Performance (Seite 2)
  - Interface Specification (Seite 6)
  - Hold / No Hold Master Mode (Seite 8)
  - Conversion of Signal Output (Seite 10)

Achten Sie darauf sich nicht in dem bestehenden Code zu verlieren, während Sie diesen untersuchen. Untersuchen Sie den
bestehenden Code vorerst nur so tief, dass Sie verstehen, wann welche Messung gestartet wird und wo die Besonderheit in
der "gleichzeitigen" Messung von Temperatur und relativer Luftfeuchtigkeit (RH - Relative Humidity) liegt

> [!TIP]
> Ihnen stehen während der Bearbeitung zwei Betreuer zur Verfügung. Greifen Sie auf deren Wissen zurück, wenn Sie nicht 
> weiterkommen. Etwas nicht zu wissen ist nicht schlimm! Verlieren Sie keine Zeit, weil Sie nicht fragen wollen. ;)

---
# Aufgaben
## 1. Mit dem Sensor vertraut machen
Nutzen Sie die in der Beschreibung genannten relevanten Kapitel des Sensor-Datenblatts um untenstehende Fragen zu
beantworten.
1. Wie lauten die Messbereiche der beiden Sensoren des SHT21?
2. Welcher Bus wird zu Kommunikation mit dem Sensor verwendet? Und welcher Übertragungs-Typ (Simplex, Half Duplex, 
Full Duplex) wir verwendet? (Tipp: Schauen Sie im Skript zu Vorlesung 8 - Serielle Kommunikation nach)
3. Lesen Sie Kapitel 5.4 Hold / No Hold Master Mode. Machen Sie sich mit den Unterschieden der beiden Modi sowie den
notwendigen Messzeiten vertraut. 
   1. Wie groß sind die maximalen Messzeiten für Temperatur und Relative Luftfeuchtigkeit, wenn wir von 14bit Auflösung
   für die Temperatur und 12bit Auflösung für die Relative Luftfeuchtigkeit ausgehen?
   2. Welchen Nachteil hat der Hold Master Mode, wenn Sie neben der Messung noch andere Aufgaben ausführen wolle?
   3. Was sollten Sie beim No Hold Master Mode beachten?
4. Notieren Sie die Formeln zur Umrechnung der Messung in Temperatur bzw. Relative Luftfeuchtigkeit. Sie werden diese
noch benötigen.

## 2. Code Untersuchen
1. Schauen Sie sich die Datei main_sht21.c and und beschreiben Sie in eigenen Worten was der Code in dieser Datei tut.
Fehlenden Code brauchen Sie nicht als solchen erläutern. Nehmen Sie z.B. bei einer fehlenden Konfiguration an, diese 
wäre vorhanden.
2. Schauen Sie sich die Datei SHT21_lib.h an um sich mit den zur Verfügung stehenden Funktionen vertraut zu machen.
Fragen Sie hier bitte nach, falls Datenstrukturen, Befehle, oder andere Dinge unklar sein sollten!
3. Schauen Sie sich nun die Datei SHT21_lib.c an. Steigen Sie hier nicht zu tief in den Code ein. Wenn Sie etwas nicht
verstehen fragen Sie entweder direkt, oder machen erstmal weiter. Eventuell klärt es sich noch von selbst.
4. Denken Sie, dass Sie ein grobes Verständnis dessen haben was SHT21_lib.h und SHT21_lib.h tun? Dann notieren Sie ihre
Gedanken und fragen uns, ob Sie auf dem richtigen Weg sind.

## 3. Endlich programmieren! :)
Da Sie nun mit dem Sensor und der SHT21_lib vertraut sind, können wir damit beginnen den Sensor in Betrieb zu nehmen.
In der Datei main_sht21.c fehlen einige Konfigurationen. Diese sind durch Kommentare gekennzeichnet.

https://github.com/Basti-iTAS-PLMS/MCON_Project_WiSe2425/blob/e706c5545c59039df6e85c25477cee6095c2b473/SHT21.X/main_sht21.c#L59-L62

Stellen Sie sich folgenden Anwendungsfall vor:
Sie wollen ihn ihrem Haus die Temperatur und Luftfeuchtigkeit durch Sensorik überprüfen (z.B. zur Vermeidung von 
Schimmelbildung). Hierzu wollen Sie in regelmäßigen Abständen die Messwerte erheben und prüfen, ob ein Lüften des Raumes
erforderlich ist.

### 3.1 Timer konfigurieren 
In unserem Anwendungsfall wäre eine stündliche Prüfung der Werte sicherlich ausreichend. Da wir heute nicht so viel Zeit
haben wollen wir die Werte jede Sekunde überprüfen.
Wie Sie bereits wissen, brauchen die Messungen des SHT21 unterschiedliche lange und liegen im Millisekundenbereich. Aus
diesem Grund benötigen wir zwei Timer. Einen zur Realisierung der Messfrequenz (1Hz) und den anderen zur Realisierung
der Verzögerung für die Messung.

Konfigurieren Sie Timer0 so, dass er jede Sekunde einen Interrupt auslöst und somit die Messung auslöst.
Timer1 soll abhängig von dem zu erhebenden Wert die nötige Verzögerung abwarten und dann ebenfalls einen Interrupt
auslösen. 
>[!TIP]
> Timer1 soll eine Funktion erfüllen, welche eine Konfiguration erfordert die von der jeweiligen Messung abhängt.
> Könnte es bereits eine geeignete Stelle in main_sht21. oder SHT21_lib.c geben an welcher diese Konfiguration besonders
> einfach durchgeführt werden kann?
> Denken Sie außerdem daran, dass man Timern einen Startwert (offset) geben kann!

### 3.2 Da stimmt doch was mit den Messwerten nicht?!
Wenn Sie die Timer korrekt konfiguriert und das Programm auf den Mikrocontroller aufgespielt haben, sollten Sie über 
den mittleren Button zwischen folgenden Anzeigen wechseln können und die jeweiligen Werte angezeigt bekommen.
1. Temperatur
2. Relative Luftfeuchtigkeit
3. Temperatur und Relative Luftfeuchtigkeit
Aber stimmen die Werte für die relative Luftfeuchtigkeit? Finden Sie den Fehler und korrigieren Sie diesen!
>[!TIP]
> Wenn Sie die STRG Taste gedrückt halten und mit der linken Maustaste auf z.B. Funktionsaufrufe klicken springt die IDE
> zur Implementierung dieser. Das könnte bei der Fehlersuche hilfreich sein. ;)

### 3.3 Optimierung des Timings
Zugegeben für unseren Anwendungsfall ist es nicht besonders wichtig, ob die Messung ein paar Millisekunden früher oder 
später ausgeführt wird und auch die Toleranz der verwendeten seriellen Kommunikation sollte groß genug sein um ein paar
Befehlstakte mehr oder weniger zu verkraften.
Stellen wir uns trotzdem einmal vor, dass unser Anwendungsfall zeitkritisch wäre. Welches Modul steht und zur Verfügung
um sicherzustellen, dass wir durch die Konfiguration des Timer-Startwerts keine Verzögerung im Timing selbst erhalten?
Wenn Sie die Lösung haben konfigurieren Sie dieses Modul für beide Timer.
>[!TIP]
> Da war doch was, dass man den aktuellen Timerwert mit einem Zielwert vergleichen kann...

### 4 Serielle Kommunikation (for experts; nicht direkt Prüfungsrelevant!)
Da Sie nun ein funktionierendes System vorliegen haben, ist es Zeit sich mit dessen Feinheiten vertraut zu machen.

Zentraler Bestandteil des Aufbaus ist die serielle Kommunikation zur Steuerung des Sensors. Schauen Sie sich hierzu die
Funktionen wrSHT21 und rdSHT21 in der Datei SHT21.c an. Diese beiden Funktionen ermöglichen das Senden von Kommandos zum
Sensor sowie das Lesen der Messwerte vom Sensor. Machen Sie sich Notizen zur Funktionsweise. 

Welches Modul ist erforderlich zur Konfiguration der seriellen Kommunikation? Wo wurde das Modul konfiguriert? Und wie
sieht die Konfiguration im Detail aus?
Haben Sie Fragen? Dann fragen Sie uns! :)

>[!NOTE]
> Ich hatte Ihnen im Moodle versprochen, dass Sie das MSSP-Modul heute kennenlernen werden. Vielleicht könnte das ja 
> Ihre Chance sein!


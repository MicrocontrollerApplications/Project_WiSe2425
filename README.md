# MCON - Semesterprojekt WiSe 24/25
[MOODLE](https://www.moodle-thu.de)
___
## Beschreibung
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
bestehenden Code vorerst nur so tief, dass Sie verstehen wann welche Messung gestartet wird und wo die Besonderheit in
der "gleichzeitigen" Messung von Temperatur und relativer Luftfeuchtigkeit (RH - Relative Humidity) liegt

> [!TIP]
> Ihnen stehen während der Bearbeitung zwei Betreuer zur Verfügung. Greifen Sie auf deren Wissen zurück, wenn Sie nicht 
> weiterkommen. Etwas nicht zu wissen ist nicht schlimm! Verlieren Sie keine Zeit, weil Sie nicht fragen wollen. ;)

---
## Aufgaben
### 1. Mit dem Sensor vertraut machen
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

### 2. Code Untersuchen
1. Schauen Sie sich die Datei main_sht21.c and und beschreiben Sie in eigenen Worten was der Code in dieser Datei tut.
Fehlenden Code brauchen Sie nicht als solchen erläutern. Nehmen Sie z.B. bei einer fehlenden Konfiguration an, diese 
wäre vorhanden.
2. 

### A3
Lorem ipsum odor amet, consectetuer adipiscing elit. Sodales pellentesque amet congue orci lacinia facilisi. Aptent semper senectus ac eget lacus tempor nascetur. Ex magnis et felis vel nisi condimentum metus. Inceptos habitasse himenaeos maecenas egestas nostra placerat. Afermentum lectus pharetra tortor sed lorem? Ad rutrum rhoncus habitasse; quis facilisi id euismod lectus. Magnis erat lorem maximus orci torquent tempor; posuere sagittis. Hac congue lorem habitant litora commodo varius.

___
## TODOs
  - [ ] Aufgabenbeschreibung anfertigen
  - [ ] Code für Studenten vorbereiten

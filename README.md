# Einfach verkettete Liste

Die einfach verkettete Liste ist eine der häufigsten und gebräuchlichsten, dynamischen Datenstrukturen. Sie zeichnet sich dadurch aus, dass Daten in einer Liste gespeichert werden, welche «in einer Richtung» durchlaufen (=iteriert) werden kann. Dabei «kennt» jedes Element in der Liste – auch als Knoten bezeichnet – seinen direkten Nachfolger-Knoten. Für den Zugriff auf die Liste wird lediglich eine Referenz auf das erste Element gespeichert. Dieses erste Element wird häufig auch als Head (=Kopf) der Liste bezeichnet.

Es ist bereits funktionierender Code für verschiedene Aspekte der Applikation vorhanden:

- C-Strukturen für die Modellierung eines Messwerts (measurement) und eines Zeitpunkts (moment)
- Ausgabe einer Menü-Struktur
- Einlesen und verarbeiten einer Menü-Option
- Hilfsfunktionen für das Einlesen und Ausgeben von Daten (Messwerten)
- Hilfsfunktionen für das Vergleichen von Datenpunkten (Vergleich von Datum/Zeit)
- Die Funktion insertAtEnd() zum Einfügen eines neuen Knotens ans Ende der einfach verketteten Liste.

Insbesondere die Funktion insertAtEnd() kann/soll als Referenz für die Implementation weiterer Listen-Operationen näher betrachtet werden.

Die nachfolgende Liste ist nach aufsteigender Schwierigkeit zum Implementieren geordnet:

- `deleteFirstElement()`: Erstes Element (Head) aus der Liste löschen
- `insertAtBeginning()`: Neuen Messwert am Anfang der Liste einfügen
- `deleteLastNode()`: Letzten Messwert aus der Liste löschen
- `deleteFirstOccurence()`: Ersten Messwert mit dem spezifizierten Wert für Datum/ Zeit aus der Liste löschen
- `insertChronologically()`: Neuen Messwert in chronologisch aufsteigender Reihenfolge in die Liste einfügen

## Contributing

This is a personal learning project for me. Please feel free to fork this repo. Pull request to submit more programs.

## Feedback

If you find any bug or have any suggestion, please do file issues. I am graceful for any feedback and will do my best to improve this package.

## License

[MIT](LICENSE) © 2020 Ioannis Christodoulakis

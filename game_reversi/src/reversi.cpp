/**
 * Praktikum Informatik 1 
 * 
 *
 * @file main.cpp
 *
 * Die Funktionen fuer das Spiel Reversi
 */

/**
* @mainpage Reversi
*
* Dokumentation des Spiels Reversi im Rahmen des Praktikums Informatik 1.
*
*/

#include <iostream>
#include <string>
#include "config.h"
#include "test.h"
#include "reversiKI.h"


/**
 * @brief Funktion zur ersten Initialisierung eines neuen Spielfelds
 *
 * Diese Funktion fuellt ein existierendes Spielfeld mit Nullen und erzeugt die Startaufstellung.
 *
 * @param spielfeld Spielfeld, das initialisiert wird
 */
void initialisiereSpielfeld(int spielfeld[GROESSE_Y][GROESSE_X])
{
    for (int j = 0; j < GROESSE_Y; j++)
        {
            for(int i = 0; i < GROESSE_X; i++)
            {
                spielfeld[j][i] = 0;
            }
        }
        spielfeld[GROESSE_Y / 2 - 1][GROESSE_X / 2 - 1] = 1;
        spielfeld[GROESSE_Y / 2][GROESSE_X / 2 - 1] = 2;
        spielfeld[GROESSE_Y / 2 - 1][GROESSE_X / 2] = 2;
        spielfeld[GROESSE_Y / 2][GROESSE_X / 2] = 1;
}



/**
* @brief Ausgabe des Spielfelds auf der Konsole
*
* Ausgabe des aktuellen Spielfelds, 0 bedeutet leeres Feld, 1 ist Spieler 1 und 2 ist Spieler2
* Kreuze symbolisieren Spieler 1, waehrend Kreise Spieler 2 symbolisieren
*
*  @param spielfeld  Spielfeld, das ausgeben wird
*/
void zeigeSpielfeld(const int spielfeld[GROESSE_Y][GROESSE_X])
{
    std::cout << "   | ";

    //Start bei ASCII 65 = A
    for (int i = 65; i < 65 + GROESSE_X; ++i)
        std::cout << ((char) i) << " | " ;

    std::cout << std::endl;

    for (int j = 0; j < GROESSE_Y; ++j)
    {
        for(int i = 0; i < GROESSE_X; ++i)
        {
            std::cout << "---+";
        }
        std::cout << "---+" << std::endl;

        std::cout << " " << j + 1 << " |";
        for (int i = 0; i < GROESSE_X; ++i)
        {
            switch (spielfeld[j][i])
            {
                case 0:
                    std::cout << "   " ;
                    break;
                case 1:
                    std::cout << " X ";
                    break;
                case 2:
                    std::cout << " O ";
                    break;
                default:
                    std::cout << "Unzulaessige Daten im Spielfeld!" << std::endl;
                    std::cout << "Abbruch .... " << std::endl;
                    exit(0);
                    break;
            }
            std::cout << "|";
        };  //for i
        std::cout <<  std::endl;
    }  //for j
}

/**
 * @brief Prueft, wer Gewinner ist
 *
 * Zaehlt alle Steine auf dem Feld
 *
 * @param spielfeld Aktuelles Spielfeld, fuer das der Gewinner ermittelt wird
 * @return winner
 */
int gewinner(const int spielfeld[GROESSE_Y][GROESSE_X])
{
    int zaehlerSpieler1 = 0;
    int zaehlerSpieler2 = 0;

    for (int j = 0; j < GROESSE_Y; ++j)
    {
        for (int i = 0; i < GROESSE_X; ++i)
        {
            if (spielfeld[j][i] == 1)
            {
                ++zaehlerSpieler1;
            }
            if (spielfeld[j][i] == 2)
            {
                ++zaehlerSpieler2;
            }

        }
    }

    if (zaehlerSpieler1 == zaehlerSpieler2)
    {
        return 0;
    }
    if (zaehlerSpieler1 < zaehlerSpieler2)
    {
        return 2;
    }
    else
    {
        return 1;
    }
}

/**
* @brief Ueberprueft fuer zwei Indizes, ob sie auf dem Spielfeld sind
*
* @param posX Index fuer die Spalte
* @param posY Index fuer die Zeile
* @return true, wenn Spalte und Zeile innerhalb des Spielfelds sind, sonst false
*/


bool aufSpielfeld(const int posX, const int posY)
{
	if( ((posX < GROESSE_X )&&(posY < GROESSE_Y)&&(posX > -1)&&(posY>-1)))
		return true;
    return false;
}


/**
 * @brief Ueberprueft fuer zwei Indizes, ob der Zug gueltig ist
 *
 *  Ueberprueft, ob auf einem benachbarten Feld ein gegnerischer Stein liegt.
 *  Wenn ja, wird diese Richtung solange untersucht, bis ein eigener Stein
 *  gefunden wird. Wird vorher der Spielfeldrand erreicht oder ein leeres Feld
 *  gefunden, wird false zurueckgegeben, sonst true
 *
 * @param spielfeld Das aktuelle Spielfeld
 * @param aktuellerSpieler Der aktuelle Spieler
 * @param posX Zu ueberpruefende Spalte
 * @param posY Zu ueberpruefende Zeile
 * @return
 */
bool zugGueltig(const int spielfeld[GROESSE_Y][GROESSE_X], const int aktuellerSpieler, const int posX, const int posY)
{
    int gegner = 3 - aktuellerSpieler; // dasselbe wie: if aktuellerSpieler == 1 -> gegner = 2
    if (spielfeld[posY][posX] != 0) // ist das Feld leer?
        {
            return false;
        }                                  //               if aktuellerSpieler == 2 -> gegner = 1


if(EIGENE_REGEL)
{
    if (spielfeld[posY][posX] != 0) // ist das Feld leer?
    {
        return false;
    } else
    {
    	if(aufSpielfeld(posY,posX))
    	{
    		return 1;
    	} else return 0;
    }
}



    // Alle Richtungen ueberpruefen bis erster gueltiger Zug gefunden
    for (int j = -1; j <= 1; j++)
    {
        for (int i = -1; i <= 1; i++)
        {
            // Hier erfolgt jetzt Ihre Im1lementierung ...
        	int k=0;
        	if(aufSpielfeld((posY+(k*i)),(posX+(k*j))))
        	if ( gegner == spielfeld[posY+i][posX+j] )          //if gegner ist gefunden
        	{													// gucken wir ob es weiter ein Verbündeter gibt
        		for ( int k = 1 ; k < 9 ; k++)
        		{
        			if(aufSpielfeld((posY+(k*i)),(posX+(k*j))))
        			{
        			if(spielfeld[posY+(k*i)][posX+(k*j)] == 0)
        				break;
        			if(spielfeld[posY+(k*i)][posX+(k*j)] == aktuellerSpieler)
        				return 1;
        			}
        		}
        	}
        }
    }
    return false;
}

/**
 * @brief Funktion prüft, ob matritzen Glaich sind
 * @return true wenn Gleich, false, wenn nicht
 */
bool sindGleich(const int eingabeFeld[GROESSE_Y][GROESSE_X], const int ergebnisFeld[GROESSE_Y][GROESSE_X])
{
	for (int j = 0; j < GROESSE_Y; ++j)
	    {
	        for (int i = 0; i < GROESSE_X; ++i)
	        {
	            if ((eingabeFeld[j][i] != ergebnisFeld[j][i]))
	            {
	            	//std::cout << "return nichtglaich!!\n\n\n";
	            return 0;
	            }
	        }
	    }
	//std::cout << "return gleich!!\n\n\n";
	return 1;
}


/**
 * @brief Funktion, die einen Zug ausfuehrt
 *
 * @param spielfeld Das aktuelle Spielfeld
 * @param aktuellerSpieler Der aktuelle Spieler
 * @param posX Die aktuelle Spalte
 * @param posY Die aktuelle Zeile
 */
void zugAusfuehren(int spielfeld[GROESSE_Y][GROESSE_X], const int aktuellerSpieler, const int posX, const int posY)
{
	if(EIGENE_REGEL)
	spielfeld[posY][posX] = aktuellerSpieler;


    int gegner = 3 - aktuellerSpieler;
    if(gegner != 3)
    {
        for (int j = -1; j <= 1; j++)
        {
            for (int i = -1; i <= 1; i++)
            {

            	int k=0;
            	if(aufSpielfeld((posY+(k*i)),(posX+(k*j))))
            	if ( gegner == spielfeld[posY+i][posX+j] )          //if gegner ist gefunden
            	{													// gucken wir ob es weiter ein Verbündeter gibt
            		for ( int k = 2 ; k < 9 ; k++)
            		{
            			if(aufSpielfeld((posY+(k*i)),(posX+(k*j))))
            			{
            			if(spielfeld[posY+(k*i)][posX+(k*j)] == 0)
            				break;
            			if(spielfeld[posY+(k*i)][posX+(k*j)] == aktuellerSpieler)
            			{ //wechsel von 1 nach 2 oder 2 nach 1
            				spielfeld[posY][posX] = aktuellerSpieler;
            				spielfeld[posY+(i)][posX+(j)] = aktuellerSpieler;
            				for ( int m = 2 ; m < 9 ; m++)
            				{
            					if(spielfeld[posY+(m*i)][posX+(m*j)] == aktuellerSpieler)
            					break;

            					spielfeld[posY+(m*i)][posX+(m*j)] = aktuellerSpieler;
            				}
            			}
            			}
            		}
            	}
            }
        }
    }
}

/**
 * @brief Gibt alle gültige Züege, wo mann mindestens ein Stein deiner gegner gewinnt
 * @return Anzahl an mögliche Zuege
 */
int moeglicheZuege(const int spielfeld[GROESSE_Y][GROESSE_X], const int aktuellerSpieler)
{
    // Hier erfolgt jetzt Ihre Implementierung ...
	int gegner = 3 - aktuellerSpieler; //сначала для каждого соперника проверим найдём рядом стоящие пустые позиции
	int count = 0;									// далее эти позиции проверим на наличие возможного Zug
	int moeg[20][3] = {};
	for (int j = 0; j < GROESSE_Y; ++j)
	{for (int i = 0; i < GROESSE_X; ++i){
		if(spielfeld[j][i] == gegner)         //wenn wir ein gegner gefunden
		{										// suchen wir nach 0 um ein stein da zu stehlen
			//std::cout << "Ein gegner ist gefunden " << j << " " << i << " \n";
													// j         3
			for (int n = -1; n <= 1; ++n)           // i  4      4
			{for (int p = -1; p <= 1; ++p){		    //	  3
				if((spielfeld[j+n][i+p] == 0))
				{
					if(zugGueltig(spielfeld,aktuellerSpieler,i+p,j+n))
					{

						//std::cout << " Zug ist Gültig " << i+l << " " << j+k << "\n";
						for(int m = 0 ; m < 20 ; m++)
						{    //   es gibt etwas        Y koord sind gleich   X koord sind gleich
							if((moeg[m][0]) == 0)
							{
								moeg[m][0] = 1;
								moeg[m][1] = i+p;
								moeg[m][2] = j+n;
								count++;
								break;
							}else{
								if(((moeg[m][1])==(i+p))&&((moeg[m][2])==(j+n)))
								{
									break;
								}
							}
						}
					}
				}
			}}
		}

	}}

//std::cout << count << " Möglicher Zuege\n";
    return count;
}

/**
 * @brief   Diese Funktion macht eine Anfragi in Consol und dann ruft Funktion zug Ausführen um den Zug aud spielfeld vorzustellen
 * @return true, wenn es ist möglich ein Zug zu machen
 */
bool menschlicherZug(int spielfeld[GROESSE_Y][GROESSE_X], const int aktuellerSpieler)
{
    if (moeglicheZuege(spielfeld, aktuellerSpieler) == 0)
    {
        return false;
    }

    int posX;
    int posY;
    std::string symbolSpieler;
    if (aktuellerSpieler == 1)
    {
        symbolSpieler = "X";
    }
    else
    {
        symbolSpieler = "O";
    }

    while (true)
    {
        std::string eingabe;
        std::cout << std::endl << "Du bist " << symbolSpieler << ". Dein Zug (z.B. A1, a1): " ;
        std::cin >> eingabe;
        posX = (int) eingabe[0] % 32 -1;
        posY = (int) eingabe[1] - 49;

        if (zugGueltig(spielfeld, aktuellerSpieler, posX, posY))
        {
            //accept turn;
            break;
        }
        else
        {
            std::cout << std::endl << "Ungueltige Eingabe !" << std::endl;
        }
    }

    zugAusfuehren(spielfeld, aktuellerSpieler, posX, posY);
    std::cout << std::endl << "Spieler " << aktuellerSpieler << " setzt auf " << (char) (posX + 65) << (posY + 1) << std::endl;

    return true;
}

/**
 * @brief nach anruf von funktion beginnt das spiel und am ende erlöutert die Ergebnisse
 */
void spielen(const int spielerTyp[2])
{
    int spielfeld[GROESSE_Y][GROESSE_X];

    //Erzeuge Startaufstellung
    initialisiereSpielfeld(spielfeld);

    int aktuellerSpieler = 1;
    zeigeSpielfeld(spielfeld);


    // solange noch Zuege bei einem der beiden Spieler moeglich sind
    //
    // Hier erfolgt jetzt Ihre Implementierung ...
    
    while((moeglicheZuege(spielfeld, 1) != 0)||(moeglicheZuege(spielfeld, 2) != 0))
    {
    	if((spielerTyp[aktuellerSpieler-1] != 2))
    	menschlicherZug(spielfeld,aktuellerSpieler);
    	else
    	computerZug(spielfeld, aktuellerSpieler);

    	zeigeSpielfeld(spielfeld);

    	if(aktuellerSpieler == 1)
    		aktuellerSpieler = 2;
    		else aktuellerSpieler = 1;
    }

    switch (gewinner(spielfeld))
    {
    case 1:
    	{
    		std::cout << "Herzlichen glückwunsch! Spieler 1 hat gewonnen!!\n\n";
    	break;
    	}
    case 2:
    	{
    		std::cout << "Spieler 2 hat gewonnen!!\n\n";
    	break;
    	}
    case 0:
    	{
    		std::cout << "Freundschaft hat gewonnen!!\n\n";
    	break;
    	}
    }
}

int main()
{
    if (TEST == 1)
    {
        bool gesamtErgebnis = ganzenTestAusfuehren();
        if (gesamtErgebnis == true)
        {
            std::cout << "ALLE TESTS BESTANDEN!" << std::endl;
        }
        else
        {
            std::cout << "MINDESTENS EIN TEST IST FEHLGESCHLAGEN!" << std::endl;
            exit(1);
        }
        std::cout << std::endl << std::endl;
    }
    
    // Die folgenden drei Zeilen werden auskommentiert oder geloescht, nachdem Sie die Funktion spielen()
    // implementiert haben (waeren sonst doppelt)
    int spielfeld[GROESSE_Y][GROESSE_X];
    char jn = 'j';
    initialisiereSpielfeld(spielfeld);

    zeigeSpielfeld(spielfeld);
    do {
    	int spielerTyp[2] = { COMPUTER, COMPUTER };
    std::cout << "Wer ist spieler 1? (1-Mensch,2-Computer) \n";
    std::cin >> spielerTyp[0];
      // Feld, das Informationen ueber den Typ des Spielers enthaelt. MENSCH(=1) oder COPMUTER(=2)
    std::cout << "\nWer ist spieler 2? (1-Mensch,2-Computer) \n";
    std::cin >> spielerTyp[1];
    spielen(spielerTyp);

    std::cout << "Möchten sie spielen noch ein Mal? (j)/(n)";
    std::cin >> jn;
    std::cin.ignore(10, '\n');
    }
    while(jn == 'j');
    // Hier erfolgt jetzt Ihre Implementierung ...
    
    return 0;
}

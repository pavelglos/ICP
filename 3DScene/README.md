# 3D scéna

## Jednotlivé body

* Pohyb myší v obou osách
    * Stisk levého tlačítka myši: pohyb nahoru
    * Stisk pravého tlačítka myši: pohyb dolu
* Ovládání pomocí kláves:
    * <kbd>W</kbd> pohyb dopředu
    * <kbd>A</kbd> pohyb doleva
    * <kbd>S</kbd> pohyb zpět
    * <kbd>D</kbd> pohyb vpravo
    * <kbd>Q</kbd> otáční vlevo kolem osy Y
    * <kbd>E</kbd> otáčení vpravo kolem osy Y
    * <kbd>F11</kbd> přepínání do a z FullScreen módu
    * <kbd>ESC</kbd> ukončení aplikace
* 3D modely
    * Height mapa: Načtená ze souboru + otexturovaná podle výšky (5 úrovní):
        * Moře
        * Písek
        * Tráva
        * Kameny se sněhem
        * Sníh
    * Krychle s texturou kamení: Pohybuje se nahoru a dolu poděl osy Y
    * Krychle s texturou ledu: Průhledná, rotuje podél osy Z 
* Požité textury: Minecraft
* 4 směrová světla tvořící dohromady slunce

## Od minula opraveno
* Pročištěn kód
* Myš: směr otáčení (byly prohozené osy) a citlivost
* Pohyb pomocí tlačítek WASD: byl implementován jen po osách
* Přepínání do FullScreen módu
* Směrové světlo (slunce): svítilo jen z jedné strany
* Moje chyba, kdy jsem do README napsal, že se krychle načítají ze souboru, což samozřejmě není pravda, jediný 3D objekt načtený ze souboru je Height mapa
* Textury na Height Mapě podle výšky: předtím byla jen obarvená podle výšky

## Lokální spuštění

Spustit exe soubor ve složce:  
```bash
/x64/Release/ICP_cvico.exe
```
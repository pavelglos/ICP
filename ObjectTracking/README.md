# Object tracking

## Jednotlivé body
* Zroj videa je web kamera
* Realtimové určení červeného objektu v 2D rastru
* použití Vláken: 
    * první vlákno určuje objekt v konkrétním obrázku a přihresluje k jeho středu zelený kříž
    * druhé vlákno zobrazuje obrázky (video) v OpenGL
* Před zobrazením se obrázek převede na texturu a až poté se zobrazí v OpenGL na vykreslení Quad
* Ukončení pomocí křížku nebo klávesou <kbd>ESC</kbd>

## Od minula opraveno
* Vyčištěn mrtvý kód
* Čisté ukončení: předtím šlo ukončit pouze kombinací kláves <kbd>CTRL</kbd> + <kbd>C</kbd>
* Problikávání obrazu: bylo způsobeno tím, že obrázky byly vykreslovány metodou glDrawPixels() a rovnou z OpenCV, takže se musel obrázek před vykreslením otočit metodou cv::flip()

## Lokální spuštění

Spustit exe soubor ve složce:  
```bash
/x64/Release/ICP_cvico.exe
```
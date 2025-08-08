install:
	bash -c "gcc src/*.c -o app `pkg-config --cflags --libs gtk+-3.0`"
	mkdir -p /usr/share/ocr-tool
	mkdir -p /usr/share/applications
	install -Dm755 app /usr/bin/ocr
	install -Dm755 src/style.css /usr/share/ocr-tool/style.css
	install -Dm755 src/ui.glade /usr/share/ocr-tool/ui.glade
	install -Dm755 ocr.desktop /usr/share/applications/ocr.desktop
	rm -rf src
	rm -rf app
	rm -rf Makefile
	rm -rf ocr.desktop

uninstall:
	sudo rm -rf /usr/share/ocr-tool
	sudo rm -rf /usr/bin/ocr
	sudo rm -rf /usr/share/applications/ocr.desktop
	rm -rf src
	rm -rf app
	rm -rf Makefile
	rm -rf ocr.desktop


clean:
	rm -f app;

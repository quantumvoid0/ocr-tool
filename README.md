# ocr-tool
A lightweight GTK based OCR tool written in C

## Installation

ocr-tool requires you to have `wl-clipboard` and `tesseract` (below given are only few distros , you can check for package name for ur own distro and install it)

| Distro          | Deps                         |
|-----------------|------------------------------|
| Arch / Manjaro  | `tesseract wl-clipboard`     |         
| Debian          | `tesseract-ocr wl-clipboard` |             
| Fedora          | `tesseract wl-clipboard`     |     

after getting dependencies

```fish
git clone https://github.com/quantumvoid0/ocr-tool
cd ocr-tool
sudo make install
```

## Uninstallaton

you can remove the dependencies listed in installation instructions and then to remove the app itself

```fish
git clone https://github.com/quantumvoid0/ocr-tool
cd ocr-tool
sudo make uninstall
```

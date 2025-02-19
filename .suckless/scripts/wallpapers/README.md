# Project Structure and Description

## Directory Structure

```
 .
├──  assets
│   └──  types
│       ├──  gallery.png
│       └──  row.png
├──  control.py
├──  lockscreen
│   └──  betterlockscreen.py
├── 󰂺 README.md
├──  rofi
│   └──  launcher.py
└──  sort.py
```

## Description

### **assets/**

This folder contains necessary images. **Do not rename this folder.** You can replace images if needed.

### **lockscreen/**

This folder contains a Python script designed to work with [Betterlockscreen](https://github.com/betterlockscreen/betterlockscreen).

#### Installation:

To install Betterlockscreen, run:

```bash
yay -S betterlockscreen
```

Customize the script and settings as needed.

### **rofi/**

The `launcher.py` script is designed to work with both Rofi and Betterlockscreen. It supports multiple display modes:

- **Gallery mode**
- **Row mode**

You can replace images in the `assets` folder as needed.

#### Customization:

- You can change the **Rofi theme** using `.wall.rasi`.
- The `rofi/types/` subfolder contains logic for selecting wallpaper display modes.

### **control.py & sort.py**

- **control.py** allows navigation between wallpapers using attributes like `[right | left]` to switch wallpapers.
- **sort.py** organizes wallpapers in `~/Pictures/wallpapers/` based on your preferences.

Feel free to improve and customize the scripts to fit your needs!

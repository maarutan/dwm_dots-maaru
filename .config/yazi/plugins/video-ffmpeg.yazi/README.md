# video-ffmpeg.yazi

> [!IMPORTANT]
> Since yazi v0.4 this plugin is already built-in (https://github.com/sxyazi/yazi/pull/1928)

A plugin for [yazi](https://github.com/sxyazi/yazi) to preview videos without using 
[ffmpegthumbnailer](https://github.com/dirkvdb/ffmpegthumbnailer) since I couldn't get it working for windows.

## Requirements

- `ffmpeg`

## Installation

```sh
ya pack -a 'Tyarel8/video-ffmpeg'
```

## Usage

Add this to your `yazi.toml`:

```toml
[plugin]
prepend_previewers = [
  { mime = "video/*", run = "video-ffmpeg" },
]

prepend_preloaders = [
  { mime = "video/*", run = "video-ffmpeg" },
]
```

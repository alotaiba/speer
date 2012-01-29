# Overview
speer is a C library which decodes speex files used in Siri protocol, to PCM 16bit Little Endian. It's used by [Asiri](https://github.com/alotaiba/SiriProxy-Asiri), the [SiriProxy](https://github.com/plamoni/SiriProxy) plugin for multi language.

## Installation
Before you install speer, you need the speex, libspeex-dev:

    sudo apt-get update
    sudo apt-get install build-essential pkg-config speex libspeex-dev
    wget the_source.tar.gz
    tar xzvf the_source.tar.gz
    cd the_source
    ./configure
    make
    sudo make install

## Usage
`speer input_speex_files_dir output_speex_files_dir`

The output will be inside `output_speex_files_dir` named "output.raw". You can use Audacity to import and play the file, or ffmpeg to encode to another format.

## License
speer is a project of Abdulrahman Al-Otaiba, the project is dual-licensed under GNU GPLv3, and MIT. See [LICENSE](https://github.com/alotaiba/speer/blob/master/LICENSE) for more details.

## Attribution
I would like to thank the following people, and give them credit for their awesome work, that without them, this project would probably never seen the light:

* Applidium guys - For their awesome work at reverse engineering the Siri proxy, and open sourcing their tools
* Pete (plamoni) - For creating the awesome SiriProxy, which this plugin runs on top of.
* Google - For providing the speech recognition service, though it's undocumented, but I have to give you guys credit for this awesome work.
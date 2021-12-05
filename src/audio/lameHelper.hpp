#include <string>
#include <windows.h>
#include "lame.h"

#define LH_STARTED WM_USER+1
#define LH_COMPUTED WM_USER+2
#define LH_DONE WM_USER+3
#define LH_ERROR WM_USER+4

#define MAX_THREAD_COUNT 5

enum encode_mode_e {
    EM_ABR,
    EM_CBR,
    EM_VBR
};

enum encode_channel_e {
    EC_MONO,
    EC_STEREO
};

enum bitrate_e {
    BR_192kbps = 192,
};

enum samplerate_e {
    SR_44khz = 44100
};

struct settings_t {
    std::string title;
    std::string artist;
    std::string album;
    std::string comment;
    std::string year;
    std::string track;
    std::string genre;
    std::string albumart;

    encode_channel_e channels;
    bitrate_e abr_bitrate;
    bitrate_e cbr_bitrate;
    int quality;
    encode_mode_e enc_mode;
    samplerate_e resample_frequency;
    samplerate_e in_samplerate;

    //The constructor; used to set default values
    settings_t();
};

class lameHelper; //lameHelper prototype, needed because of struct StaticParam_t

//Use to hold parameters for the thread function
struct StaticParam_t {
    std::string pcm;
    std::string mp3;
    settings_t settings;
    WNDPROC callback_proc;
    lameHelper *lhObj;
};


class lameHelper {
private:
    static const int PCM_SIZE = 4096;
    static const int MP3_SIZE = 4096;

    HANDLE hThread[MAX_THREAD_COUNT];
    StaticParam_t *hSParam[MAX_THREAD_COUNT];

    int encode_x(const std::string &, const std::string &, const settings_t &, WNDPROC);

    void WriteWaveHeader(FILE *, int, int, int, int);

    void write_32_bits_low_high(FILE *, int);

    void write_16_bits_low_high(FILE *, int);

    int set_id3_albumart(lame_t gfp, char const *file_name);

    void errorHandler(const char *);

    char errMsg[1000];
public:
    lameHelper();

    ~lameHelper();

    //Encode a pcm file to mp3
    int encode(const std::string &pcm_in, const std::string &mp3_out);

    //Decode a mp3 to pcm
    int decode(const std::string &mp3_in, const std::string &pcm_out);

    int decode(const std::string &mp3_in, const std::string &, WNDPROC callback_proc);

};

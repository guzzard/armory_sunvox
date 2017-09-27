#include "Sunvox.h"

#ifdef KORE_MACOS
#include <Kore/System.h>
extern const char* macgetresourcepath();
#endif

#ifdef KORE_WINDOWS
#define dlerror GetLastError
#define dlsym GetProcAddress
#define dlclose FreeLibrary
#define SUNVOX_FN_ATTR __stdcall
#else
#define SUNVOX_FN_ATTR /**/
#endif

extern "C" typedef int(SUNVOX_FN_ATTR *init_t)(const char* dev, int freq, int channels, unsigned int flags);
extern "C" typedef int(SUNVOX_FN_ATTR *deinit_t)();
extern "C" typedef int(SUNVOX_FN_ATTR *open_slot_t)(int slot);
extern "C" typedef int(SUNVOX_FN_ATTR *close_slot_t)(int slot);
extern "C" typedef int(SUNVOX_FN_ATTR *lock_slot_t)(int slot);
extern "C" typedef int(SUNVOX_FN_ATTR *unlock_slot_t)(int slot);
extern "C" typedef int(SUNVOX_FN_ATTR *load_t)(int slot, const char* name);
extern "C" typedef int(SUNVOX_FN_ATTR *volume_t)(int slot, int vol);
extern "C" typedef int(SUNVOX_FN_ATTR *play_t)(int slot);
extern "C" typedef int(SUNVOX_FN_ATTR *play_from_beginning_t)(int slot);
extern "C" typedef int(SUNVOX_FN_ATTR *stop_t)(int slot);

init_t init_f = 0;
deinit_t deinit_f = 0;
open_slot_t open_slot_f = 0;
close_slot_t close_slot_f = 0;
lock_slot_t lock_slot_f = 0;
unlock_slot_t unlock_slot_f = 0;
load_t load_f = 0;
volume_t volume_f = 0;
play_t play_f = 0;
play_from_beginning_t play_from_beginning_f = 0;
stop_t stop_f = 0;

Sunvox::Sunvox() {
    handle = NULL;
}

int Sunvox::load_lib() {
#ifdef KORE_LINUX
    handle = dlopen("./sunvox.so", RTLD_LAZY);
#elif KORE_MACOS
    char name[1024];
    strcpy(name, macgetresourcepath());
    strcat(name, "/osx/sunvox.dylib");
    handle = dlopen(name, RTLD_LAZY);
#elif KORE_WINDOWS
	handle = LoadLibrary(TEXT("sunvox.dll"));
#endif

    if (!handle) {
        std::cerr << "Cannot open library: " << dlerror() << std::endl;
        return -1;
    }
    return load_functions_from_lib();
}

int Sunvox::load_functions_from_lib() {
    init_f = (init_t) dlsym(handle, "sv_init");
    if (!init_f) {
        std::cerr << "Cannot load function sv_init." << std::endl;
        return -1;
    }
    deinit_f = (deinit_t) dlsym(handle, "sv_deinit");
    if (!deinit_f) {
        std::cerr << "Cannot load function sv_deinit." << std::endl;
        return -1;
    }
    open_slot_f = (open_slot_t) dlsym(handle, "sv_open_slot");
    if (!open_slot_f) {
        std::cerr << "Cannot load function sv_open_slot." << std::endl;
        return -1;
    }
    close_slot_f = (close_slot_t) dlsym(handle, "sv_close_slot");
    if (!close_slot_f) {
        std::cerr << "Cannot load function sv_close_slot." << std::endl;
        return -1;
    }
    lock_slot_f = (lock_slot_t) dlsym(handle, "sv_lock_slot");
    if (!lock_slot_f) {
        std::cerr << "Cannot load function sv_lock_slot." << std::endl;
        return -1;
    }
    unlock_slot_f = (unlock_slot_t) dlsym(handle, "sv_unlock_slot");
    if (!unlock_slot_f) {
        std::cerr << "Cannot load function sv_unlock_slot." << std::endl;
        return -1;
    }
    load_f = (load_t) dlsym(handle, "sv_load");
    if (!load_f) {
        std::cerr << "Cannot load function sv_load." << std::endl;
        return -1;
    }
    volume_f = (volume_t) dlsym(handle, "sv_volume");
    if (!volume_f) {
        std::cerr << "Cannot load function sv_volume." << std::endl;
        return -1;
    }
    play_f = (play_t) dlsym(handle, "sv_play");
    if (!play_f) {
        std::cerr << "Cannot load function sv_play." << std::endl;
        return -1;
    }
    play_from_beginning_f = (play_from_beginning_t) dlsym(handle, "sv_play_from_beginning");
    if (!play_from_beginning_f) {
        std::cerr << "Cannot load function sv_play_from_beginning." << std::endl;
        return -1;
    }
    stop_f = (stop_t) dlsym(handle, "sv_stop");
    if (!stop_f) {
        std::cerr << "Cannot load function sv_stop." << std::endl;
        return -1;
    }
    return 0;
}

int Sunvox::unload_lib() {
    int close = dlclose(handle);
    if (close != 0) {
        std::cerr << "Cannot close library: " << dlerror() << std::endl;
        return -1;
    }
    return 0;
}

int Sunvox::init(const char* dev, int freq, int channels, unsigned int flags) {
    int init = init_f(dev, freq, channels, flags);
    if (init <= 0) {
        std::cerr << "Cannot init sunvox. Returned: " << init << std::endl;
        return init;
    } else {
        int major = (init >> 16) & 255;
        int minor1 = (init >> 8) & 255;
        int minor2 = (init) & 255;
        std::cout << "SunVox lib version: " << major << "." << minor1 << "." << minor2 << std::endl;
    }
    return 0;
}

int Sunvox::deinit() {
    int deinit = deinit_f();
    if (deinit != 0) {
        std::cerr << "Cannot deinit sunvox. Returned: " << deinit << std::endl;
        return deinit;
    }
    return 0;
}

int Sunvox::open_slot(int slot) {
    if (open_slots.count(slot) != 0) {
        return -2;
    }
    int open_slot = open_slot_f(slot);
    if (open_slot != 0) {
        return open_slot;
    }
    open_slots.insert(slot);
    return 0;
}

int Sunvox::close_slot(int slot) {
    if (open_slots.count(slot) != 1) {
        return -2;
    }
    int close_slot = close_slot_f(slot);
    if (close_slot != 0) {
        return close_slot;
    }
    open_slots.erase(slot);
    return 0;
}

int Sunvox::close_all_open_slots() {
    int ret = 0;
    for (std::set<int>::iterator it = open_slots.begin(); it != open_slots.end(); ++it) {
        int close = close_slot(*it);
        if (close != 0) {
            ret = close;
        }
    }
    return ret;
}

int Sunvox::lock_slot(int slot) {
    if (locked_slots.count(slot) != 0) {
        return -2;
    }
    int lock_slot = lock_slot_f(slot);
    if (lock_slot != 0) {
        return lock_slot;
    }
    locked_slots.insert(slot);
    return 0;
}

int Sunvox::unlock_slot(int slot) {
    if (locked_slots.count(slot) != 1) {
        return -2;
    }
    int unlock_slot = unlock_slot_f(slot);
    if (unlock_slot != 0) {
        return unlock_slot;
    }
    locked_slots.erase(slot);
    return 0;
}

int Sunvox::load(int slot, const char* name) {
#ifdef KORE_MACOS
    char path[1024];
    strcpy(path, macgetresourcepath());
    strcat(path, "/osx/");
    strcat(path, name);
    int load = load_f(slot, path);
#else
    int load = load_f(slot, name);
#endif
    if (load != 0) {
        return load;
    }
    return 0;
}

// set slot volume
int Sunvox::volumne(int slot, int vol) {
    int volumne = volume_f(slot, vol);
    if (volumne != 0) {
        return volumne;
    }
    return 0;
}

// start playback of slot
int Sunvox::play(int slot) {
    int play = play_f(slot);
    if (play != 0) {
        return play;
    }
    return 0;
}

// start playback from begining of slot
int Sunvox::play_from_beginning(int slot) {
    int play_from_beginning = play_from_beginning_f(slot);
    if (play_from_beginning != 0) {
        return play_from_beginning;
    }
    return 0;
}

// stop playback of slot
int Sunvox::stop(int slot) {
    int stop = stop_f(slot);
    if (stop != 0) {
        return stop;
    }
    return 0;
}

#ifndef _SUNVOX_H_
#define _SUNVOX_H_

#include <dlfcn.h>
#include <iostream>
#include <set>

class Sunvox {
public:
    Sunvox();
    int load_lib(); // load sunvox lib from disk
    int unload_lib(); // unload sunvox lib
    int init(const char* dev, int freq, int channels, unsigned int flags); // init sunvox
    int deinit(); // deinint sunvox
    int open_slot(int slot); // open audio slot
    int close_slot(int slot); // close audio slot
    int close_all_open_slots();  // closes all open audio slots
    int load(int slot, const char* name); // load module from file or memory
    int volumne(int slot, int vol); // set slot volume
    int play(int slot); // start playback of slot
    int play_from_beginning(int slot); // start playback from begining of slot
    int stop(int slot); // stop playback of slot
    
private:
    void* handle;
    
    std::set<int> open_slots;
    std::set<int> locked_slots;

    int load_functions_from_lib(); // loads all functions from sunvox lib

    int lock_slot(int slot); // locks audio slot - needed when running certain commands
    int unlock_slot(int slot); // unlocks audio slot

};
 
#endif // _SUNVOX_H_

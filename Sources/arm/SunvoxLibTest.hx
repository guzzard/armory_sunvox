package arm;

#if kha_kore
import armory.system.Input;
import sunvox.Sunvox;
#end

class SunvoxLibTest extends armory.Trait {
	
	#if kha_kore
	var sv:Sunvox;
	var sunvox_load_lib = -1;
	var sunvox_init = -1;
	var open_slot = -1;
	#end
	
	public function new() {
		super();

		notifyOnInit(function() {

			#if kha_kore
			sv = Sunvox.create();
			initSunvox();
			#end
		});

		notifyOnUpdate(function() {
			#if kha_kore
			if(Input.getKeyboard().released("i")){
				if(sunvox_init == -1){
					initSunvox();
				}
			}
			if(Input.getKeyboard().released("l")){
				trace("load song: " + sv.load(0, "8bit_tales.sunvox"));
			}

			if(Input.getKeyboard().released("p")){
				trace("play: " + sv.play(0));
			}

			if(Input.getKeyboard().released("b")){
				trace("play from begining: " + sv.play_from_beginning(0));
			}

			if(Input.getKeyboard().released("s")){
				trace("stop: " + sv.stop(0));
			}
			if(Input.getKeyboard().released("x")){
				trace("close slots, deinit, unload");
				if(open_slot == 0){
					var close_slot = sv.close_slot(0);
					trace("close_slot: " + close_slot);
				}
				if(sunvox_init == 0){
					var sunvox_deinit = sv.deinit();
					trace("sunvox_deinit: " + sunvox_deinit);
				}
				var sunvox_unload_lib = sv.unload_lib();
				trace("sunvox_unload_lib: " + sunvox_unload_lib);
				sunvox_init = -1;
			}
			#end
		});

		// notifyOnRemove(function() {
		// });
	}

	function initSunvox(){
		#if kha_kore
		sunvox_load_lib = sv.load_lib();
		trace("sunvox_load_lib: " + sunvox_load_lib);

		if(sunvox_load_lib == 0){

			sunvox_init = sv.init('0', 44100, 2, 0);
			trace("sunvox_init: " + sunvox_init);

			if(sunvox_init == 0){
				open_slot = sv.open_slot(0);
				trace("open_slot: " + open_slot);
			}
		}
		#end
	}
}

package;

import kha.Framebuffer;
import kha.Scheduler;
import kha.System;
import sunvox.Sunvox;

class Empty {
	public function new() {
		System.notifyOnRender(render);
		Scheduler.addTimeTask(update, 0, 1 / 60);

		var sv = Sunvox.create();
		var sunvox_load_lib = sv.load_lib();
		trace("sunvox_load_lib: " + sunvox_load_lib);

		if(sunvox_load_lib == 0){

			var sunvox_init = sv.init('0', 44100, 2, 0);
			trace("sunvox_init: " + sunvox_init);

			if(sunvox_init == 0){
				var open_slot = sv.open_slot(0);
				trace("open_slot: " + open_slot);

				sv.load(0, "8bit_tales.sunvox");
				sv.play(0);
			}
		}
	}

	function update(): Void {
		
	}

	function render(framebuffer: Framebuffer): Void {		
	}
}

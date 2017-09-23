package sunvox;

#if kha_kore

@:include("Sunvox.h")
@:native("Sunvox")
@:unreflective
@:structAccess
extern class Sunvox {
	@:native("Sunvox")
	public static function create():Sunvox;
	public function load_lib():Int;
	public function unload_lib():Int;
	public function init(dev:String, freq:Int, channels:Int, flags:UInt):Int;
	public function deinit():Int;
	public function open_slot(slot:Int):Int;
	public function close_slot(slot:Int):Int;
	public function close_all_open_slots():Int;
	public function load(slot:Int, name:String):Int;
	public function volumne(slot:Int, vol:Int):Int;
	public function play(slot:Int):Int;
	public function play_from_beginning(slot:Int):Int;
	public function stop(slot:Int):Int;
}

#elseif js

class Sunvox {
	public static function create():Sunvox { return new Sunvox(); }
	function new() {}
	public function load_lib(done:Int->Void):Void {
		kha.LoaderImpl.loadBlobFromDescription({ files: ["sunvox.js"] }, function(b:kha.Blob) {
            untyped __js__("(1, eval)({0})", b.toString());
            done(0);
        });
	}
	public function unload_lib():Int { return -1; }
	public function init(dev:String, freq:Int, channels:Int, flags:UInt):Int { return -1; }
	public function deinit():Int { return -1; }
	public function open_slot(slot:Int):Int { return -1; }
	public function close_slot(slot:Int):Int { return -1; }
	public function close_all_open_slots():Int { return -1; }
	public function load(slot:Int, name:String):Int { return -1; }
	public function volumne(slot:Int, vol:Int):Int { return -1; }
	// sunvox.js does not expose more control yet
	public function play(slot:Int):Int { untyped __js__("Module.sv_init_play()"); return -1; }
	public function play_from_beginning(slot:Int):Int { return -1; }
	public function stop(slot:Int):Int { return -1; }
}

#end

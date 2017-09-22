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

#end
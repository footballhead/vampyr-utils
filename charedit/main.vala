/**
 * @brief The main class for the Vampyr character editor.
 */
public class CharacterEditor : Gtk.Window {
	/** @brief The data model behind the player data. */
	private PlayerModel? model = null;
	/** @brief A reference to the save button, so we can disable it. */
	private Gtk.Button save_btn;
	/** @brief Where the name is entered. */
	NameValuePair name_pair;
	/** @brief Where race is chosen */
	RaceDropdownBox race_dropdown;
	/** @brief Where level is entered. */
	IntEntry level_entry;
	/** @brief Where life is entered. */
	IntEntry life_entry;
	/** @brief Place for entering gold. */
	IntEntry gold_entry;
	/** @brief Place for entering XP. */
	IntEntry exp_entry;
	/** @brief Place for modifying magic. */
	IntEntry magic_entry;

	/** @brief Create the main window and initialize all the widgets. */
	public CharacterEditor () {
		this.title = "Vampyr Character Editor";
		this.window_position = Gtk.WindowPosition.CENTER;
		this.destroy.connect (Gtk.main_quit);
		this.set_default_size (350, 100);
		// TODO make unresizable

		create_interface ();
	}

	/** @brief Add all the widgets to the window. */
	private void create_interface () {
		Gtk.Box box = new Gtk.Box (Gtk.Orientation.VERTICAL, 0);


		var open_btn = new Gtk.Button.with_label ("Open...");
		open_btn.clicked.connect (open_chooser);

		save_btn = new Gtk.Button.with_label ("Save");
		save_btn.clicked.connect (save_character);
		save_btn.set_sensitive (true);

		var save_open_box = new Gtk.Box (Gtk.Orientation.HORIZONTAL, 0);
		save_open_box.pack_start (open_btn, true, true, 4);
		save_open_box.pack_start (save_btn, true, true, 4);
		box.pack_start (save_open_box, false, false, 4);


		name_pair = new NameValuePair ("Name", "");
		name_pair.entry.changed.connect (name_changed);
		box.pack_start (name_pair, false, false, 0);

		race_dropdown = new RaceDropdownBox ("Race", Race.all_as_string ());
		race_dropdown.combobox.changed.connect(() => {
			model.set_race ( Race.from_string (race_dropdown.get_value ()));
		});
		box.pack_start (race_dropdown, false, false, 0);

		level_entry = new IntEntry ("Level", 0, 255, 0);
		level_entry.int_entry.value_changed.connect(() => {
			model.set_level (level_entry.get_value_as_int ());
		});
		box.pack_start (level_entry, false, false, 0);

		exp_entry = new IntEntry ("XP", -2147483648, 2147483647, 0);
		exp_entry.int_entry.value_changed.connect(() => {
			model.set_exp (exp_entry.get_value_as_int ());
		});
		box.pack_start (exp_entry, false, false, 0);

		life_entry = new IntEntry ("Life", -32768, 32767, 0);
		life_entry.int_entry.value_changed.connect(() => {
			model.set_life (life_entry.get_value_as_int ());
		});
		box.pack_start (life_entry, false, false, 0);

		magic_entry = new IntEntry ("Magic", 0, 255, 0);
		magic_entry.int_entry.value_changed.connect(() => {
			model.set_magic (magic_entry.get_value_as_int ());
		});
		box.pack_start (magic_entry, false, false, 0);

		gold_entry = new IntEntry ("Gold", -32768, 32767, 0);
		gold_entry.int_entry.value_changed.connect(() => {
			model.set_gold (gold_entry.get_value_as_int ());
		});
		box.pack_start (gold_entry, false, false, 0);


		this.add (box);
	}

	/**
	 * @brief Open the file chooser and load a save if selected.
	 * @remark A callback for clicking the "Open..." button.
	 */
	private void open_chooser () {
		var chooser = new Gtk.FileChooserDialog (
				"Select your favorite file", this, Gtk.FileChooserAction.OPEN,
				"_Cancel", Gtk.ResponseType.CANCEL,
				"_Open", Gtk.ResponseType.ACCEPT);

		if (chooser.run () == Gtk.ResponseType.ACCEPT) {
			model = new PlayerModel (chooser.get_file ());
			save_btn.set_sensitive (true);
			name_pair.set_value (model.get_name ());
			race_dropdown.set_value (model.get_race ());
			level_entry.set_value (model.get_level ());
			life_entry.set_value (model.get_life ());
			gold_entry.set_value (model.get_gold ());
			exp_entry.set_value (model.get_exp ());
			magic_entry.set_value (model.get_magic ());
		}

		chooser.close ();
	}

	/**
	 * @brief Callback called whenever the player name is modified.
	 * @remark Here we impose a 10 character limit on the name field to indicate
	 *         that names are only stored as 10 characters in the file.
	 */
	private void name_changed () {
		string new_name = name_pair.get_value ();
		if (new_name.length > 10) {
			name_pair.set_value (new_name.slice (0,10));
		}

		model.set_name (new_name);
	}

	/**
	 * @brief Save the modified character data to the file.
	 * @remark A callback for clicking the "Save" button.
	 */
	private void save_character () {
		model.save ();
	}

	/**
	 * @brief The program entry point; create the GUI and start accepting input.
	 * @param args Command-line arguments.
	 */
	public static int main (string[] args) {
		Gtk.init (ref args);

		var app = new CharacterEditor ();
		app.show_all ();
		Gtk.main ();
		return 0;
	}
}

class NameValuePair : Gtk.Box {
	Gtk.Label name_label;
	public Gtk.Entry entry;

	public NameValuePair (string name, string def_val) {
		this.orientation = Gtk.Orientation.HORIZONTAL;
		this.spacing = 0;

		name_label = new Gtk.Label (name);
		entry = new Gtk.Entry ();
		set_value (def_val);

		this.pack_start (name_label, false, false, 0 );
		this.pack_start (entry, true, true, 0 );

		stdout.printf ("DEBUG: label name: %s\n", name);
	}

	public string get_value () {
		return entry.get_text();
	}

	public void set_value (string val) {
		entry.set_text (val);
	}
}

class RaceDropdownBox : Gtk.Box {
	Gtk.Label name_label;
	public Gtk.ComboBoxText combobox;

	public RaceDropdownBox (string name, string[] def_val) {
		this.orientation = Gtk.Orientation.HORIZONTAL;
		this.spacing = 0;

		name_label = new Gtk.Label (name);
		combobox = new Gtk.ComboBoxText ();
		foreach (unowned string str in def_val) {
			combobox.append_text (str);
		}

		this.pack_start (name_label, false, false, 0 );
		this.pack_start (combobox, true, true, 0 );
	}

	public string get_value () {
		return combobox.get_active_text();
	}

	public void set_value (Race race) {
		combobox.set_active (race);
	}
}



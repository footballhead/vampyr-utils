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
	NameValuePair level_pair;

	/** @brief Create the main window and initialize all the widgets. */
	public CharacterEditor () {
		this.title = "Vampyr Character Editor";
		this.window_position = Gtk.WindowPosition.CENTER;
		this.destroy.connect (Gtk.main_quit);
		this.set_default_size (350, 70);
		// TODO make unresizable

		create_interface ();
	}

	/** @brief Add all the widgets to the window. */
	private void create_interface () {
		var open_btn = new Gtk.Button.with_label ("Open...");
		open_btn.clicked.connect (open_chooser);

		save_btn = new Gtk.Button.with_label ("Save");
		save_btn.clicked.connect (save_character);
		save_btn.set_sensitive (true);

		var save_open_box = new Gtk.Box (Gtk.Orientation.HORIZONTAL, 0);
		save_open_box.pack_start (open_btn, true, true, 4);
		save_open_box.pack_start (save_btn, true, true, 4);

		name_pair = new NameValuePair ("Name", "");
		name_pair.entry.changed.connect (name_changed);

		race_dropdown = new RaceDropdownBox ("Race", Race.all_as_string ());
		race_dropdown.combobox.changed.connect(() => {
			model.set_race ( Race.from_string (race_dropdown.get_value ()));
		});

		level_pair = new NameValuePair ("Level", "");
		level_pair.entry.changed.connect (level_changed);

		Gtk.Box box = new Gtk.Box (Gtk.Orientation.VERTICAL, 0);
		box.pack_start (save_open_box, false, false, 4);
		box.pack_start (name_pair, false, false, 4);
		box.pack_start (race_dropdown, false, false, 4);
		box.pack_start (level_pair, false, false, 4);

		this.add (box);
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

	private void level_changed () {
		string new_level_str = level_pair.get_value ();
		int new_level_int = int.parse (new_level_str);
		if (new_level_int > 255) {
			level_pair.set_value ("255");
		} else if (new_level_int < 0) {
			level_pair.set_value ("0");
		}

		model.set_level (new_level_int);
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
			level_pair.set_value (model.get_level ().to_string ());
		}

		chooser.close ();
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

		this.pack_start (name_label, true, true, 4 );
		this.pack_start (entry, true, true, 4 );
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

		this.pack_start (name_label, true, true, 4 );
		this.pack_start (combobox, true, true, 4 );
	}

	public string get_value () {
		return combobox.get_active_text();
	}

	public void set_value (Race race) {
		combobox.set_active (race);
	}
}



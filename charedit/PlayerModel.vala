/**
 * @brief The data model underlying player save files.
 */
class PlayerModel {
	/** @brief The file we are loaded from */
	private File file;
	/**
	 * @brief The raw file data we manipulate then save.
	 * @remark Manipulation only happens during save()
	 * @remark Player saves on disk are ALWAYS 77 bytes long.
	 */
	private uint8[] raw_buffer = new uint8[77];
	/** @brief The player name, never more than 10 characters. */
	private string name;
	/** @brief A valid player race. */
	private Race race;
	/** @brief The player level; always between 0 and 255. */
	private int level;
	/** @brief The player life, in the range of a signed short */
	private int life;

	/**
	 * @brief Load a player from a save file.
	 * @param file The file of disk to load from.
	 */
	public PlayerModel (File file) {
		this.file = file;

		var input = file.read();
		input.read( raw_buffer );
		input.close ();

		// Get the name part of the file and turn it into a string
		string formatter = "";
		foreach (uint8 c in raw_buffer[1:11]) {
			formatter += "%c".printf (c);
		}
		set_name (formatter.strip ());

		race = (Race)raw_buffer[11];
		level = (int)raw_buffer[12];
		life = 0 | raw_buffer[13] | (raw_buffer[14] << 8);
	}

	/**
	 * @brief Save changes to the same file we loaded from.
	 */
	public void save () {
		for (int i = 1; i < 11; i++) {
			raw_buffer[i] = ' ';
		}

		for (int i = 0; i < name.length; i++) {
			raw_buffer[i+1] = name.data[i];
		}

		raw_buffer[11] = (uint8)race;
		raw_buffer[12] = (uint8)level;
		// this assumption only holds on little endian machines (I think)
		raw_buffer[13] = (uint8)(life & 0xff);
		raw_buffer[14] = (uint8)( (life >> 8) & 0xff );
		// set current life to max life
		raw_buffer[15] = (uint8)(life & 0xff);
		raw_buffer[16] = (uint8)( (life >> 8) & 0xff );

		FileIOStream iostream = file.open_readwrite ();
		OutputStream output = iostream.output_stream;
		size_t bytes_written = 0;
		output.write_all (raw_buffer, out bytes_written);
	}


	public File get_file () {
		return this.file;
	}

	public string get_name () {
		return name;
	}

	/**
	 * @brief Set the player name, sanitizing input.
	 * @param new_name The name we want to use.
	 * @remark Makes sure the name is not more than 10 characters.
	 */
	public void set_name (string new_name) {
		var short_name = new_name;

		if (new_name.length > 10) {
			short_name = new_name.slice (0,10);
		}

		name = short_name;
		stdout.printf ("DEBUG: %s\n", short_name);
	}

	public Race get_race () {
		return race;
	}

	public void set_race (Race race) {
		this.race = race;
		stdout.printf ("DEBUG: Set race %s\n", race.to_string ());
	}

	/**
	 * @brief Set the player level, sanitizing input.
	 * @param new_level The level we want to use.
	 * @remark The level must be an unsigned byte (0-255).
	 */
	public void set_level (int new_level) {
		int valid_level = new_level.clamp (0, 255);
		level = valid_level;
		stdout.printf ("DEBUG: Set level %d\n", valid_level);
	}

	public int get_level () {
		return level;
	}

	/**
	 * @brief Set the player life, sanitizing input.
	 * @param new_life The life value we want to use.
	 * @remark The life must be an signed short (-32768 to 32767).
	 * @remark Life represents both current and max.
	 */
	public void set_life (int new_life) {
		int valid_life = new_life.clamp (-32768, 32767);
		life = valid_life;
		stdout.printf ("DEBUG: Set life %d\n", valid_life);
	}

	public int get_life () {
		return life;
	}

}

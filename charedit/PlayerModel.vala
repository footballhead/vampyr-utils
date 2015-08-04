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
	/** @brief Current amount of gold the player is carrying. */
	private int gold;
	/** @brief Current player XP. */
	private int xp;
	/** @brief Current and max player Magic. */
	private int magic;

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
		// next 2 bytes are current life, which we don't care about
		set_gold (0 | raw_buffer[17] | (raw_buffer[18] << 8));
		set_exp (0 | raw_buffer[19] | (raw_buffer[20] << 8) | (raw_buffer[21] << 16) | (raw_buffer[22] << 24));
		set_magic (raw_buffer[23]);
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

		raw_buffer[17] = (uint8)(gold & 0xff);
		raw_buffer[18] = (uint8)((gold >> 8) & 0xff);

		raw_buffer[19] = (uint8)(xp & 0xff);
		raw_buffer[20] = (uint8)((xp >> 8) & 0xff);
		raw_buffer[21] = (uint8)((xp >> 16) & 0xff);
		raw_buffer[22] = (uint8)((xp >> 24) & 0xff);

		raw_buffer[23] = (uint8)magic;
		raw_buffer[24] = (uint8)magic;

		FileIOStream iostream = file.open_readwrite ();
		OutputStream output = iostream.output_stream;
		size_t bytes_written = 0;
		output.write_all (raw_buffer, out bytes_written);
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

	/**
	 * @brief Set the player life, sanitizing input.
	 * @param new_life The life value we want to use.
	 * @remark The life must be an signed short (-32768 to 32767).
	 * @remark Life represents both current and max; whenever you save we
	 *         essentially heal your character.
	 */
	public void set_life (int new_life) {
		int valid_life = new_life.clamp (-32768, 32767);
		life = valid_life;
		stdout.printf ("DEBUG: Set life %d\n", valid_life);
	}

	/**
	 * @brief Set the player gold, sanitizing input.
	 * @param new_gold The gold value we want to use.
	 * @remark The gold must be an signed short (-32768 to 32767).
	 */
	public void set_gold (int new_gold) {
		gold = new_gold.clamp (-32768, 32767);
		stdout.printf ("DEBUG: Set gold %d\n", gold);
	}

	/**
	 * @brief Set the player XP, sanitizing input.
	 * @param new_exp The new value for XP.
	 */
	public void set_exp (int new_exp) {
		xp = new_exp;
		stdout.printf ("DEBUG: Set XP %d\n", xp);
	}

	public void set_magic (int new_magic) {
		magic = new_magic.clamp (0, 255);
		stdout.printf ("DEBUG: Set Magic %d\n", magic);
	}

	//public File get_file () {
	//	return this.file;
	//}

	public string get_name () {
		return name;
	}

	public Race get_race () {
		return race;
	}

	public int get_level () {
		return level;
	}

	public int get_life () {
		return life;
	}

	public int get_gold () {
		return gold;
	}

	public int get_exp () {
		return xp;
	}

	public int get_magic () {
		return magic;
	}
}


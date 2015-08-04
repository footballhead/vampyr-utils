/**
 * @brief All valid races with their byte values, and some conversion functions.
 */
enum Race {
	HUMAN = 0,
	DWARF = 1,
	ELF = 2,
	CORINTIR = 3,
	VICTOR_SHAO = 4,
	BRIAN_WESTON = 5;

    /**
     * @brief Convert a Race to its corresponding textual representation.
     * @return The string that represents that Race.
     */
	public string to_string () {
		switch (this) {
			case HUMAN: return "Human";
			case DWARF: return "Dwarf";
			case ELF: return "Elf";
			case CORINTIR: return "Corintir";
			case VICTOR_SHAO: return "Victor Shao";
			case BRIAN_WESTON: return "Brian Weston";
			default: assert_not_reached ();
		}
	}

    /**
     * @brief Convert a textual representation of a Race to the right enum.
     * @param race_str The string representation of the Race
     * @return The corresponding Race
     */
	public static Race from_string (string race_str) {
		switch (race_str) {
			case "Human": return HUMAN;
			case "Dwarf": return DWARF;
			case "Elf": return ELF;
			case "Corintir": return CORINTIR;
			case "Victor Shao": return VICTOR_SHAO;
			case "Brian Weston": return BRIAN_WESTON;
			default: assert_not_reached ();
		}
	}

    /**
     * @brief Get an array of all valid textual representations of Races.
     * @return A list of strings, one per race.
     */
	public static string[] all_as_string() {
		return { "Human", "Dwarf", "Elf", "Corintir", "Victor Shao", "Brian Weston" };
	}
}

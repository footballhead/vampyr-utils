/** @brief A panel with a label and a place to enter ints */
class IntEntry : Gtk.Box {
	/** @brief A label attached to the component. */
	private Gtk.Label label;
	/** @brief The highest possible value that can be entered */
	private double upper_bound;
	/** @brief The lowest possible value that can be entered */
	private double lower_bound;

	/** @brief Spin Button for entering numbers; public to connect signals. */
	public Gtk.SpinButton int_entry;

	/**
	 * @brief Create a new integer entry component.
	 * @param label The label text to use.
	 * @param low The lowest possible value.
	 * @param high The highest possible value.
	 * @param def_val The default value.
	 */
	public IntEntry (string label, double low, double high, double def_value)
			requires (low <= high)
			requires (low <= def_value && def_value <= high)
	{
		this.orientation = Gtk.Orientation.HORIZONTAL;
		this.spacing = 0;

		this.lower_bound = low;
		this.upper_bound = high;

		this.label = new Gtk.Label (label);
		this.int_entry = new Gtk.SpinButton.with_range (low, high, 1);

		set_value (def_value);

		this.pack_start (this.label, false, false, 4);
		this.pack_start (this.int_entry, true, true, 4);
	}

	/**
	 * @brief Get the currently entered number as an integer.
	 * @return The value of the spin button.
	 */
	public int get_value_as_int () {
		return int_entry.get_value_as_int();
	}

	/**
	 * @brief Get the currently entered number as a double.
	 * @return The value of the spin button.
	 */
	public double get_value () {
		return int_entry.get_value ();
	}



	/**
	 * @brief Modify the currently entered value.
	 * @param new_value The new value to use; must be within component bounds.
	 */
	public void set_value (double new_value)
			requires (this.lower_bound <= new_value)
			requires (new_value <= this.upper_bound)
	{
		int_entry.set_value (new_value);
	}
}


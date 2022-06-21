
.PHONY: all
all: gui_tab.py mux.py

%.py: %.grc
	grcc $^

# creates a placeholder .py file to make make happy
.make_pattern_gen: pattern_gen.grc
	grcc $^
	touch $@

.PHONY: clean
clean:
	rm -fv *.py .make_*

.PHONY: Debug
Debug:
	$(CXX) --version
	cd test; $(MAKE) Debug
	cd sample; $(MAKE) Debug
	cd benchmark; $(MAKE) Debug
.PHONY: Release
Release:
	$(CXX) --version
	cd test; $(MAKE) Release
	cd sample; $(MAKE) Release
	cd benchmark; $(MAKE) Release
.PHONY: clean
clean:
	cd test; $(MAKE) clean
	cd sample; $(MAKE) clean
	cd benchmark; $(MAKE) clean

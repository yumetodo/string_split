.PHONY: Debug
Debug:
	$(CXX) --version
	cd test; make Debug
	cd sample; make Debug
	cd benchmark; make Debug
.PHONY: Release
Release:
	$(CXX) --version
	cd test; make Release
	cd sample; make Release
	cd benchmark; make Release
.PHONY: clean
clean:
	cd test; make clean
	cd sample; make clean
	cd benchmark; make clean

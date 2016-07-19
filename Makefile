.PHONY: Debug
Debug:
	$(CXX) --version
	cd test; make Debug
	cd sample; make Debug
.PHONY: Release
Release:
	$(CXX) --version
	cd test; make Release
	cd sample; make Release
.PHONY: clean
clean:
	cd test; make clean
	cd sample; make clean

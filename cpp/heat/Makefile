include ../make.settings

## Set ADIOS_DIR here or before doing make
override ADIOS_INC=-I${ADIOS_DIR}/include
override ADIOS_LIB=`${ADIOS_DIR}/bin/adios2-config --libs`

default: simulation analysis
all: default


%.o : %.cpp
	${CXX} ${CXXFLAGS} -c ${ADIOS_INC} -o $@ $< 

simulation: simulation/HeatTransfer.o simulation/IO_adios2.o simulation/Settings.o simulation/heatSimulation.o
	${CXX} ${CXXFLAGS} -o heatSimulation $^ ${ADIOS_LIB} 

analysis: analysis/heatAnalysis.o analysis/AnalysisSettings.o 
	${CXX} ${CXXFLAGS} -o heatAnalysis $^ ${ADIOS_LIB} 

clean:
	rm -f simulation/*.o analysis/*.o core.*
	rm -f heatSimulation heatAnalysis heatVisualization

distclean: clean
	rm -f *.png *.pnm core core.*
	rm -rf *.bp *.bp.dir 
	rm -f *.h5
	rm -f conf *.bpflx




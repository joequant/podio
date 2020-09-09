#include "read_test.h"
#include "podio/SIOReader.h"

#include "datamodel/EventInfoSIOBlock.h" // here to get the factory working properly

int main(){
//  auto reader = podio::SIOReader();
  podio::SIOReader reader; // SIOReader has no copy c'tor ...
  auto store = podio::EventStore();
  reader.openFile("example.sio");
  store.setReader(&reader);

  try{
    unsigned nEvents = 1410065408 ;
    for(unsigned i=0; i<nEvents; ++i) {

      if(i%1000==0)
        std::cout<<"reading event "<<i<<std::endl;

      reader.readEvent() ;

      processEvent(store, true, i);

      // only clear collections for re-use
      store.clearCollections();
      store.clearCaches(); // Would be done in EventStore::clear
      // store.clear();    // However, this would delete the collections as well ...
      reader.endOfEvent();

    }
  }
  catch( sio::exception &e ) {
    if( e.code() != sio::error_code::eof ) {
      SIO_RETHROW( e, e.code(), "SIOReader::readStream: Couldn't read stream" ) ;
    }
  }

  reader.closeFile();
  return 0;
}
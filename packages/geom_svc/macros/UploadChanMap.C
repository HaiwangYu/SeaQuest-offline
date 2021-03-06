/// UploadChanMap.C:  Macro to upload the channel mapping from tsv file to MySQL DB.
R__LOAD_LIBRARY(libchan_map)

int UploadChanMap()
{
  gSystem->Load("libchan_map.so");

  /// Select one of the classes.
  ChanMapTaiwan map;
  //ChanMapV1495  map;
  //ChanMapScaler map;
  //CalibParamXT map;
  //CalibParamInTimeTaiwan map;
  //CalibParamInTimeV1495 map;
  //GeomParamPlane map;

  /// Set a map ID.
  const std::string map_id="e906run28740";
//  const std::string map_id="G9_run5_2";

  map.SetMapIDbyFile(map_id);
  map.ReadFromFile();
  //map.Print(cout);
  map.WriteToLocalFile("output_for_check.tsv");
  map.WriteToDB();
  map.WriteRangeToDB();

  return 0;
}

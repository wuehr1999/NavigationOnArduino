/******************************************************************************
  Parses osm file content (as String) to osm map object.
  The string was generated from a simplified *.osm ( done with JOSM ) and
  the osmfileToStringTool in the library repository.
  Libraries: NavigationOnArduino,
                               ArduinoQueue:
https://github.com/EinarArnason/ArduinoQueue

  Original Creation Date: 18.10.2020
******************************************************************************/
#include <Map.h>

// OSM string
const char osmString[] =
    "<?xml version='1.0' encoding='UTF-8'?><osm version='0.6' "
    "generator='JOSM'>  <node id='-102309' action='modify' visible='true' "
    "lat='48.99851876231' lon='12.82617821162' /> <node id='-102310' "
    "action='modify' visible='true' lat='49.00062086193' lon='12.82310411162' "
    "/>  <node id='-102311' action='modify' visible='true' "
    "lat='48.99941976215' lon='12.82118121162' />  <node id='-102312' "
    "action='modify' visible='true' lat='49.00103576186' lon='12.82202251162' "
    "/>  <node id='-102313' action='modify' visible='true' "
    "lat='48.99974636209' lon='12.82491421162' />  <node id='-102314' "
    "action='modify' visible='true' lat='48.99875206227' lon='12.82575931162' "
    "/>  <node id='-102315' action='modify' visible='true' "
    "lat='48.99795606242' lon='12.82723611162' />  <node id='-102316' "
    "action='modify' visible='true' lat='48.99919646219' lon='12.82166681162' "
    "/>  <node id='-102317' action='modify' visible='true' "
    "lat='48.99972726209' lon='12.82368231162' />  <node id='-102318' "
    "action='modify' visible='true' lat='48.99771406246' lon='12.82354061162' "
    "/>  <node id='-102319' action='modify' visible='true' "
    "lat='49.00089076188' lon='12.82336001162' />  <node id='-102320' "
    "action='modify' visible='true' lat='49.000235362' lon='12.82138381162' /> "
    " <node id='-102321' action='modify' visible='true' lat='48.99984626207' "
    "lon='12.82556811162' />  <node id='-102322' action='modify' "
    "visible='true' lat='48.99778716245' lon='12.82762451162' />  <node "
    "id='-102323' action='modify' visible='true' lat='49.00142116179' "
    "lon='12.82214701162' />  <node id='-102324' action='modify' "
    "visible='true' lat='49.00137366179' lon='12.82252121162' />  <node "
    "id='-102325' action='modify' visible='true' lat='48.99946606214' "
    "lon='12.82264181162' />  <node id='-102326' action='modify' "
    "visible='true' lat='49.00070726192' lon='12.82312031162' />  <node "
    "id='-102327' action='modify' visible='true' lat='49.00064366193' "
    "lon='12.82170551162' />  <node id='-102328' action='modify' "
    "visible='true' lat='48.99612966275' lon='12.82469671162' />  <node "
    "id='-102329' action='modify' visible='true' lat='48.99947276214' "
    "lon='12.82255831162' />  <node id='-102330' action='modify' "
    "visible='true' lat='49.00046636196' lon='12.82255761162' />  <node "
    "id='-102331' action='modify' visible='true' lat='48.9996714621' "
    "lon='12.82237041162' />  <node id='-102332' action='modify' "
    "visible='true' lat='48.99550326286' lon='12.82537081162' />  <node "
    "id='-102333' action='modify' visible='true' lat='48.99882706226' "
    "lon='12.82187281162' />  <node id='-102334' action='modify' "
    "visible='true' lat='48.99731886253' lon='12.82385911162' />  <node "
    "id='-102335' action='modify' visible='true' lat='48.99960926212' "
    "lon='12.82133441162' />  <node id='-102336' action='modify' "
    "visible='true' lat='48.99988516207' lon='12.82543911162' />  <node "
    "id='-102337' action='modify' visible='true' lat='48.99891116224' "
    "lon='12.82713781162' />  <node id='-102338' action='modify' "
    "visible='true' lat='49.00162026175' lon='12.82197891162' />  <node "
    "id='-102339' action='modify' visible='true' lat='49.00139826179' "
    "lon='12.82293531162' />  <node id='-102340' action='modify' "
    "visible='true' lat='48.99954236213' lon='12.82189151162' />  <node "
    "id='-102341' action='modify' visible='true' lat='48.99545936287' "
    "lon='12.82538471162' />  <node id='-102342' action='modify' "
    "visible='true' lat='48.99922816218' lon='12.82233781162' />  <node "
    "id='-102343' action='modify' visible='true' lat='48.99815456238' "
    "lon='12.82702831162' />  <node id='-102344' action='modify' "
    "visible='true' lat='49.00030966199' lon='12.82301341162' />  <node "
    "id='-102345' action='modify' visible='true' lat='48.99648446268' "
    "lon='12.82547431162' />  <node id='-102346' action='modify' "
    "visible='true' lat='48.99911356221' lon='12.82721231162' />  <node "
    "id='-102347' action='modify' visible='true' lat='49.00149296177' "
    "lon='12.82260001162' />  <node id='-102348' action='modify' "
    "visible='true' lat='49.00000756204' lon='12.82357891162' />  <node "
    "id='-102349' action='modify' visible='true' lat='48.99867156229' "
    "lon='12.82587021162' />  <node id='-102350' action='modify' "
    "visible='true' lat='49.00169686174' lon='12.82216101162' />  <node "
    "id='-102351' action='modify' visible='true' lat='48.99897416223' "
    "lon='12.82569841162' />  <node id='-102352' action='modify' "
    "visible='true' lat='48.99975506209' lon='12.82379611162' />  <node "
    "id='-102353' action='modify' visible='true' lat='48.99986926207' "
    "lon='12.82225571162' />  <node id='-102354' action='modify' "
    "visible='true' lat='48.99910766221' lon='12.82737741162' />  <node "
    "id='-102355' action='modify' visible='true' lat='49.00039536197' "
    "lon='12.82200561162' />  <node id='-102356' action='modify' "
    "visible='true' lat='48.99687226261' lon='12.82405231162' />  <node "
    "id='-102357' action='modify' visible='true' lat='48.99703266258' "
    "lon='12.82631821162' />  <node id='-102358' action='modify' "
    "visible='true' lat='49.00013696202' lon='12.82136101162' />  <node "
    "id='-102359' action='modify' visible='true' lat='48.99904236222' "
    "lon='12.82565591162' />  <node id='-102360' action='modify' "
    "visible='true' lat='49.00070776192' lon='12.82289761162' />  <node "
    "id='-102361' action='modify' visible='true' lat='48.99893606224' "
    "lon='12.82712711162' />  <node id='-102362' action='modify' "
    "visible='true' lat='49.00043566197' lon='12.82151921162' />  <node "
    "id='-102363' action='modify' visible='true' lat='48.99659966266' "
    "lon='12.82566361162' />  <node id='-102364' action='modify' "
    "visible='true' lat='48.9991540622' lon='12.82703201162' />  <node "
    "id='-102365' action='modify' visible='true' lat='48.99937456216' "
    "lon='12.82657431162' />  <node id='-102366' action='modify' "
    "visible='true' lat='49.00041256197' lon='12.82229171162' />  <node "
    "id='-102367' action='modify' visible='true' lat='48.99825946236' "
    "lon='12.82681231162' />  <node id='-102368' action='modify' "
    "visible='true' lat='48.99953926213' lon='12.82227191162' />  <node "
    "id='-102369' action='modify' visible='true' lat='48.99992076206' "
    "lon='12.82512441162' />  <node id='-102370' action='modify' "
    "visible='true' lat='48.99911326221' lon='12.82557781162' />  <node "
    "id='-102371' action='modify' visible='true' lat='48.99906526221' "
    "lon='12.82781831162' />  <node id='-102372' action='modify' "
    "visible='true' lat='48.99980136208' lon='12.82570051162' />  <node "
    "id='-102373' action='modify' visible='true' lat='49.00048256196' "
    "lon='12.82313101162' />  <node id='-102374' action='modify' "
    "visible='true' lat='48.99962716211' lon='12.82601001162' />  <node "
    "id='-102375' action='modify' visible='true' lat='48.99924046218' "
    "lon='12.82178501162' />  <node id='-102376' action='modify' "
    "visible='true' lat='48.99700536259' lon='12.82403911162' />  <node "
    "id='-102377' action='modify' visible='true' lat='49.00057016194' "
    "lon='12.82258201162' />  <node id='-102378' action='modify' "
    "visible='true' lat='48.99985966207' lon='12.82498661162' />  <node "
    "id='-102379' action='modify' visible='true' lat='48.99963806211' "
    "lon='12.82227951162' />  <node id='-102380' action='modify' "
    "visible='true' lat='48.99948876214' lon='12.82283441162' />  <node "
    "id='-102381' action='modify' visible='true' lat='48.99955196213' "
    "lon='12.82612081162' />  <node id='-102382' action='modify' "
    "visible='true' lat='48.99930636217' lon='12.82238151162' />  <node "
    "id='-102383' action='modify' visible='true' lat='48.99677056263' "
    "lon='12.82411731162' />  <node id='-102384' action='modify' "
    "visible='true' lat='48.99617906274' lon='12.82481551162' />  <node "
    "id='-102385' action='modify' visible='true' lat='48.99882316226' "
    "lon='12.82708491162' />  <node id='-102386' action='modify' "
    "visible='true' lat='48.99949846214' lon='12.82622461162' />  <node "
    "id='-102387' action='modify' visible='true' lat='49.00123776182' "
    "lon='12.82267831162' />  <node id='-102388' action='modify' "
    "visible='true' lat='48.99946946214' lon='12.82273791162' />  <node "
    "id='-102389' action='modify' visible='true' lat='48.99851076232' "
    "lon='12.82678221162' />  <node id='-102390' action='modify' "
    "visible='true' lat='49.00043916196' lon='12.82261121162' />  <node "
    "id='-102391' action='modify' visible='true' lat='48.99801256241' "
    "lon='12.82726221162' />  <node id='-102392' action='modify' "
    "visible='true' lat='48.99838926234' lon='12.82650951162' />  <node "
    "id='-102393' action='modify' visible='true' lat='48.99957576212' "
    "lon='12.82459181162' />  <node id='-102394' action='modify' "
    "visible='true' lat='49.00076166191' lon='12.82317641162' />  <node "
    "id='-102395' action='modify' visible='true' lat='48.99963386211' "
    "lon='12.82343611162' />  <node id='-102396' action='modify' "
    "visible='true' lat='48.99907296221' lon='12.82760051162' />  <node "
    "id='-102397' action='modify' visible='true' lat='48.99680666263' "
    "lon='12.82592391162' />  <node id='-102398' action='modify' "
    "visible='true' lat='49.00032226199' lon='12.82142611162' />  <node "
    "id='-102399' action='modify' visible='true' lat='48.99983886207' "
    "lon='12.82391081162' />  <node id='-102400' action='modify' "
    "visible='true' lat='49.00095036187' lon='12.82339621162' />  <node "
    "id='-102401' action='modify' visible='true' lat='48.99562746284' "
    "lon='12.82527621162' />  <node id='-102402' action='modify' "
    "visible='true' lat='49.00095566187' lon='12.82192401162' />  <node "
    "id='-102403' action='modify' visible='true' lat='49.00052466195' "
    "lon='12.82255651162' />  <node id='-102404' action='modify' "
    "visible='true' lat='49.00145636178' lon='12.82269891162' />  <node "
    "id='-102405' action='modify' visible='true' lat='49.00137756179' "
    "lon='12.82323701162' />  <node id='-102406' action='modify' "
    "visible='true' lat='48.9997013621' lon='12.82485771162' />  <node "
    "id='-102407' action='modify' visible='true' lat='49.00000886204' "
    "lon='12.82135711162' />  <node id='-102408' action='modify' "
    "visible='true' lat='48.99839386234' lon='12.82259211162' />  <node "
    "id='-102409' action='modify' visible='true' lat='48.99954316213' "
    "lon='12.82218731162' />  <node id='-102410' action='modify' "
    "visible='true' lat='49.00151916177' lon='12.82196961162' />  <node "
    "id='-102411' action='modify' visible='true' lat='49.00011446202' "
    "lon='12.82278541162' />  <node id='-102412' action='modify' "
    "visible='true' lat='49.00128646181' lon='12.82233701162' />  <node "
    "id='-102413' action='modify' visible='true' lat='49.00113136184' "
    "lon='12.82260751162' />  <node id='-102414' action='modify' "
    "visible='true' lat='48.99935876216' lon='12.82125781162' />  <node "
    "id='-102415' action='modify' visible='true' lat='49.00139036179' "
    "lon='12.82300661162' />  <node id='-102416' action='modify' "
    "visible='true' lat='48.99685736262' lon='12.82598741162' />  <node "
    "id='-102417' action='modify' visible='true' lat='48.99909756221' "
    "lon='12.82747801162' />  <node id='-102418' action='modify' "
    "visible='true' lat='48.99992156206' lon='12.82520441162' />  <node "
    "id='-102419' action='modify' visible='true' lat='48.99852166231' "
    "lon='12.82244641162' />  <node id='-102420' action='modify' "
    "visible='true' lat='49.00089326188' lon='12.82187791162' />  <node "
    "id='-102421' action='modify' visible='true' lat='49.000257662' "
    "lon='12.82293831162' />  <node id='-102422' action='modify' "
    "visible='true' lat='49.00098236187' lon='12.82194911162' />  <node "
    "id='-102423' action='modify' visible='true' lat='49.00015776202' "
    "lon='12.82333671162' />  <node id='-102424' action='modify' "
    "visible='true' lat='48.99903696222' lon='12.82196721162' />  <node "
    "id='-102425' action='modify' visible='true' lat='48.99944436215' "
    "lon='12.82635491162' />  <node id='-102426' action='modify' "
    "visible='true' lat='49.0013466618' lon='12.82267131162' />  <node "
    "id='-102427' action='modify' visible='true' lat='48.99921336219' "
    "lon='12.82175971162' />  <node id='-102428' action='modify' "
    "visible='true' lat='49.000228762' lon='12.82324411162' />  <node "
    "id='-102429' action='modify' visible='true' lat='48.99932596217' "
    "lon='12.82182411162' />  <node id='-102430' action='modify' "
    "visible='true' lat='49.00008666203' lon='12.82270241162' />  <node "
    "id='-102431' action='modify' visible='true' lat='48.99887536225' "
    "lon='12.82719621162' />  <node id='-102432' action='modify' "
    "visible='true' lat='48.99901466222' lon='12.82146121162' />  <node "
    "id='-102433' action='modify' visible='true' lat='48.99975236209' "
    "lon='12.82580801162' />  <node id='-102434' action='modify' "
    "visible='true' lat='48.9991188622' lon='12.82713711162' />  <node "
    "id='-102435' action='modify' visible='true' lat='49.00143796178' "
    "lon='12.82206061162' />  <node id='-102436' action='modify' "
    "visible='true' lat='49.00119316183' lon='12.82229991162' />  <node "
    "id='-102437' action='modify' visible='true' lat='48.99976956209' "
    "lon='12.82410111162' />  <node id='-102438' action='modify' "
    "visible='true' lat='48.9964045627' lon='12.82441431162' />  <node "
    "id='-102439' action='modify' visible='true' lat='49.00040516197' "
    "lon='12.82167741162' />  <node id='-102440' action='modify' "
    "visible='true' lat='48.99919476219' lon='12.82171581162' />  <node "
    "id='-102441' action='modify' visible='true' lat='49.00016446201' "
    "lon='12.82285011162' />  <node id='-102442' action='modify' "
    "visible='true' lat='48.99895256224' lon='12.82187871162' />  <node "
    "id='-102443' action='modify' visible='true' lat='48.99781796244' "
    "lon='12.82311891162' />  <node id='-102444' action='modify' "
    "visible='true' lat='48.99950546213' lon='12.82241781162' />  <node "
    "id='-102445' action='modify' visible='true' lat='48.99881986226' "
    "lon='12.82686951162' />  <node id='-102446' action='modify' "
    "visible='true' lat='49.00141496179' lon='12.82231281162' />  <node "
    "id='-102447' action='modify' visible='true' lat='49.00109316185' "
    "lon='12.82340411162' />  <node id='-102448' action='modify' "
    "visible='true' lat='48.99959086212' lon='12.82224741162' />  <node "
    "id='-102449' action='modify' visible='true' lat='48.99948296214' "
    "lon='12.82249301162' />  <node id='-102450' action='modify' "
    "visible='true' lat='48.99930296217' lon='12.82673921162' />  <node "
    "id='-102451' action='modify' visible='true' lat='48.99990776206' "
    "lon='12.82531801162' />  <node id='-102452' action='modify' "
    "visible='true' lat='48.99883636226' lon='12.82715421162' />  <node "
    "id='-102453' action='modify' visible='true' lat='48.99966246211' "
    "lon='12.82231241162' />  <node id='-102454' action='modify' "
    "visible='true' lat='48.99976446209' lon='12.82391531162' />  <node "
    "id='-102455' action='modify' visible='true' lat='48.99782616244' "
    "lon='12.82753371162' />  <node id='-102456' action='modify' "
    "visible='true' lat='49.00117056183' lon='12.82350931162' />  <node "
    "id='-102457' action='modify' visible='true' lat='48.9996766621' "
    "lon='12.82134271162' />  <node id='-102458' action='modify' "
    "visible='true' lat='49.00161566175' lon='12.82234781162' />  <node "
    "id='-102459' action='modify' visible='true' lat='48.99933346217' "
    "lon='12.82092981162' />  <node id='-102460' action='modify' "
    "visible='true' lat='49.00123246182' lon='12.82232231162' />  <node "
    "id='-102461' action='modify' visible='true' lat='48.9996837621' "
    "lon='12.82592671162' />  <node id='-102462' action='modify' "
    "visible='true' lat='48.99539956288' lon='12.82539001162' />  <node "
    "id='-102463' action='modify' visible='true' lat='48.99591056279' "
    "lon='12.82499921162' />  <node id='-102464' action='modify' "
    "visible='true' lat='49.00003426204' lon='12.82248701162' />  <node "
    "id='-102465' action='modify' visible='true' lat='48.99872536228' "
    "lon='12.82210181162' />  <node id='-102466' action='modify' "
    "visible='true' lat='48.9974974625' lon='12.82374141162' />  <node "
    "id='-102467' action='modify' visible='true' lat='48.99934166216' "
    "lon='12.82515531162' />  <node id='-102468' action='modify' "
    "visible='true' lat='49.00106986185' lon='12.82260681162' />  <node "
    "id='-102469' action='modify' visible='true' lat='48.99954276213' "
    "lon='12.82204081162' />  <node id='-102470' action='modify' "
    "visible='true' lat='49.00155096176' lon='12.82246461162' />  <node "
    "id='-102471' action='modify' visible='true' lat='48.99998616205' "
    "lon='12.82239781162' />  <node id='-102472' action='modify' "
    "visible='true' lat='48.99881936226' lon='12.82571991162' />  <node "
    "id='-102473' action='modify' visible='true' lat='48.99989626206' "
    "lon='12.82504351162' />  <node id='-102474' action='modify' "
    "visible='true' lat='49.00168616174' lon='12.82203261162' />  <node "
    "id='-102475' action='modify' visible='true' lat='49.00071606191' "
    "lon='12.82271101162' />  <node id='-102476' action='modify' "
    "visible='true' lat='48.99952036213' lon='12.82235801162' />  <node "
    "id='-102477' action='modify' visible='true' lat='48.99883276226' "
    "lon='12.82694521162' />  <node id='-102478' action='modify' "
    "visible='true' lat='49.00167236174' lon='12.82225911162' />  <node "
    "id='-102479' action='modify' visible='true' lat='49.00036996198' "
    "lon='12.82315631162' />  <node id='-102480' action='modify' "
    "visible='true' lat='48.99951906213' lon='12.82127491162' />  <node "
    "id='-102481' action='modify' visible='true' lat='49.0013513618' "
    "lon='12.82239651162' />  <node id='-102482' action='modify' "
    "visible='true' lat='48.99962646211' lon='12.82199591162' />  <node "
    "id='-102483' action='modify' visible='true' lat='48.9991213622' "
    "lon='12.82220331162' />  <node id='-102484' action='modify' "
    "visible='true' lat='49.00064196193' lon='12.82263671162' />  <node "
    "id='-102485' action='modify' visible='true' lat='48.99874486227' "
    "lon='12.82679111162' />  <node id='-102486' action='modify' "
    "visible='true' lat='48.99927686218' lon='12.82146391162' />  <node "
    "id='-102487' action='modify' visible='true' lat='48.99677846263' "
    "lon='12.82591351162' />  <node id='-102488' action='modify' "
    "visible='true' lat='48.99974446209' lon='12.82419481162' />  <node "
    "id='-102489' action='modify' visible='true' lat='48.99778246245' "
    "lon='12.82327281162' />  <node id='-102490' action='modify' "
    "visible='true' lat='48.99879356226' lon='12.82682181162' />  <node "
    "id='-102491' action='modify' visible='true' lat='49.00118406183' "
    "lon='12.82266041162' />  <node id='-102492' action='modify' "
    "visible='true' lat='48.99954576213' lon='12.82182511162' />  <node "
    "id='-102493' action='modify' visible='true' lat='48.99990736206' "
    "lon='12.82375551162' />  <way id='-101847' action='modify' "
    "visible='true'>    <nd ref='-102371' />    <nd ref='-102396' />    <nd "
    "ref='-102417' />    <nd ref='-102354' />    <nd ref='-102346' />    <nd "
    "ref='-102434' />    <nd ref='-102364' />    <nd ref='-102450' />    <nd "
    "ref='-102365' />    <nd ref='-102425' />    <nd ref='-102386' />    <nd "
    "ref='-102381' />    <nd ref='-102374' />    <nd ref='-102461' />    <nd "
    "ref='-102433' />    <nd ref='-102372' />    <nd ref='-102321' />    <nd "
    "ref='-102336' />    <nd ref='-102451' />    <nd ref='-102418' />    <nd "
    "ref='-102369' />    <nd ref='-102473' />    <nd ref='-102378' />    <nd "
    "ref='-102313' />    <nd ref='-102406' />    <nd ref='-102393' />    <nd "
    "ref='-102488' />    <nd ref='-102437' />    <nd ref='-102399' />    <nd "
    "ref='-102493' />    <nd ref='-102348' />    <nd ref='-102423' />    <nd "
    "ref='-102428' />    <nd ref='-102479' />    <nd ref='-102373' />    <nd "
    "ref='-102310' />    <nd ref='-102326' />    <nd ref='-102394' />    <nd "
    "ref='-102319' />    <nd ref='-102400' />    <nd ref='-102447' />    <nd "
    "ref='-102415' />    <nd ref='-102339' />    <tag k='highway' v='path' />  "
    "  <tag k='source' v='Bing' />    <tag k='tracktype' v='grade2' />  </way> "
    " <way id='-101848' action='modify' visible='true'>    <nd ref='-102405' "
    "/>    <nd ref='-102415' />    <tag k='tracktype' v='grade2' />  </way>  "
    "<way id='-101849' action='modify' visible='true'>    <nd ref='-102444' /> "
    "   <nd ref='-102382' />    <nd ref='-102342' />    <nd ref='-102483' />   "
    " <nd ref='-102424' />    <nd ref='-102442' />    <nd ref='-102333' />  "
    "</way>  <way id='-101850' action='modify' visible='true'>    <nd "
    "ref='-102330' />    <nd ref='-102366' />    <nd ref='-102355' />    <nd "
    "ref='-102439' />    <nd ref='-102362' />    <tag k='tracktype' v='grade4' "
    "/>  </way>  <way id='-101851' action='modify' visible='true'>    <nd "
    "ref='-102339' />    <nd ref='-102426' />    <nd ref='-102324' />    <nd "
    "ref='-102481' />    <nd ref='-102412' />    <nd ref='-102460' />    <nd "
    "ref='-102436' />    <nd ref='-102312' />    <nd ref='-102422' />    <nd "
    "ref='-102402' />    <nd ref='-102420' />    <nd ref='-102327' />    <nd "
    "ref='-102362' />    <nd ref='-102398' />    <nd ref='-102320' />    <nd "
    "ref='-102358' />    <nd ref='-102407' />    <nd ref='-102457' />    <nd "
    "ref='-102335' />    <nd ref='-102480' />    <nd ref='-102311' />    <tag "
    "k='highway' v='path' />    <tag k='source' v='Bing' />    <tag "
    "k='tracktype' v='grade2' />  </way>  <way id='-101852' action='modify' "
    "visible='true'>    <nd ref='-102470' />    <nd ref='-102347' />    <nd "
    "ref='-102404' />    <nd ref='-102339' />    <tag k='source' v='Bing' />   "
    " <tag k='tracktype' v='grade2' />  </way>  <way id='-101853' "
    "action='modify' visible='true'>    <nd ref='-102476' />    <nd "
    "ref='-102379' />    <nd ref='-102353' />  </way>  <way id='-101854' "
    "action='modify' visible='true'>    <nd ref='-102328' />    <nd "
    "ref='-102384' />    <nd ref='-102345' />    <nd ref='-102363' />    <nd "
    "ref='-102487' />    <nd ref='-102397' />    <nd ref='-102416' />    <nd "
    "ref='-102357' />    <nd ref='-102315' />    <nd ref='-102391' />  </way>  "
    "<way id='-101855' action='modify' visible='true'>    <nd ref='-102311' /> "
    "   <nd ref='-102459' />    <tag k='highway' v='track' />    <tag "
    "k='source' v='Bing' />    <tag k='tracktype' v='grade1' />  </way>  <way "
    "id='-101856' action='modify' visible='true'>    <nd ref='-102367' />    "
    "<nd ref='-102392' />    <nd ref='-102309' />    <nd ref='-102349' />    "
    "<nd ref='-102314' />    <nd ref='-102472' />    <nd ref='-102351' />    "
    "<nd ref='-102359' />    <nd ref='-102370' />    <nd ref='-102467' />    "
    "<nd ref='-102393' />  </way>  <way id='-101857' action='modify' "
    "visible='true'>    <nd ref='-102486' />    <nd ref='-102432' />    <nd "
    "ref='-102333' />    <nd ref='-102465' />    <nd ref='-102419' />    <nd "
    "ref='-102408' />    <nd ref='-102443' />    <nd ref='-102489' />    <nd "
    "ref='-102318' />    <nd ref='-102466' />    <nd ref='-102334' />    <nd "
    "ref='-102376' />    <nd ref='-102356' />    <nd ref='-102383' />    <nd "
    "ref='-102438' />    <nd ref='-102328' />    <nd ref='-102463' />    <nd "
    "ref='-102401' />    <nd ref='-102332' />    <nd ref='-102341' />    <nd "
    "ref='-102462' />  </way>  <way id='-101858' action='modify' "
    "visible='true'>    <nd ref='-102434' />    <nd ref='-102361' />    <nd "
    "ref='-102337' />    <nd ref='-102431' />    <nd ref='-102452' />    <nd "
    "ref='-102385' />    <nd ref='-102477' />    <nd ref='-102445' />    <nd "
    "ref='-102490' />    <nd ref='-102485' />    <nd ref='-102389' />    <nd "
    "ref='-102367' />  </way>  <way id='-101859' action='modify' "
    "visible='true'>    <nd ref='-102456' />    <nd ref='-102447' />    <tag "
    "k='tracktype' v='grade2' />  </way>  <way id='-101860' action='modify' "
    "visible='true'>    <nd ref='-102344' />    <nd ref='-102390' />    <nd "
    "ref='-102330' />    <nd ref='-102403' />    <nd ref='-102377' />    <nd "
    "ref='-102484' />    <nd ref='-102475' />    <nd ref='-102468' />    <nd "
    "ref='-102413' />    <nd ref='-102491' />    <nd ref='-102387' />    <nd "
    "ref='-102426' />    <tag k='highway' v='path' />    <tag k='source' "
    "v='Bing' />    <tag k='tracktype' v='grade2' />  </way>  <way "
    "id='-101861' action='modify' visible='true'>    <nd ref='-102340' />    "
    "<nd ref='-102482' />    <nd ref='-102353' />    <nd ref='-102471' />    "
    "<nd ref='-102464' />    <nd ref='-102430' />    <nd ref='-102411' />    "
    "<nd ref='-102441' />    <nd ref='-102421' />    <nd ref='-102344' />    "
    "<nd ref='-102479' />    <tag k='highway' v='path' />    <tag k='source' "
    "v='Bing' />    <tag k='tracktype' v='grade2' />  </way>  <way "
    "id='-101862' action='modify' visible='true'>    <nd ref='-102475' />    "
    "<nd ref='-102360' />    <nd ref='-102326' />    <tag k='highway' v='path' "
    "/>    <tag k='source' v='Bing' />    <tag k='tracktype' v='grade2' />  "
    "</way>  <way id='-101863' action='modify' visible='true'>    <nd "
    "ref='-102335' />    <nd ref='-102492' />    <nd ref='-102340' />    <nd "
    "ref='-102469' />    <nd ref='-102409' />    <nd ref='-102368' />    <nd "
    "ref='-102476' />    <nd ref='-102444' />    <nd ref='-102449' />    <nd "
    "ref='-102329' />    <nd ref='-102325' />    <nd ref='-102388' />    <nd "
    "ref='-102380' />    <nd ref='-102395' />    <nd ref='-102317' />    <nd "
    "ref='-102352' />    <nd ref='-102454' />    <nd ref='-102437' />    <tag "
    "k='highway' v='path' />    <tag k='source' v='Bing' />    <tag "
    "k='tracktype' v='grade2' />  </way>  <way id='-101864' action='modify' "
    "visible='true'>    <nd ref='-102409' />    <nd ref='-102448' />    <nd "
    "ref='-102379' />    <nd ref='-102453' />    <nd ref='-102331' />  </way>  "
    "<way id='-101865' action='modify' visible='true'>    <nd ref='-102446' /> "
    "   <nd ref='-102470' />    <nd ref='-102458' />    <nd ref='-102478' />   "
    " <nd ref='-102350' />    <nd ref='-102474' />    <nd ref='-102338' />    "
    "<nd ref='-102410' />    <nd ref='-102435' />    <nd ref='-102323' />    "
    "<nd ref='-102446' />    <nd ref='-102481' />    <tag k='tracktype' "
    "v='grade2' />  </way>  <way id='-101866' action='modify' visible='true'>  "
    "  <nd ref='-102367' />    <nd ref='-102343' />    <nd ref='-102391' />    "
    "<nd ref='-102455' />    <nd ref='-102322' />  </way>  <way id='-101867' "
    "action='modify' visible='true'>    <nd ref='-102311' />    <nd "
    "ref='-102414' />    <nd ref='-102486' />    <nd ref='-102316' />    <nd "
    "ref='-102440' />    <nd ref='-102427' />    <nd ref='-102375' />    <nd "
    "ref='-102429' />    <nd ref='-102492' />    <tag k='foot' v='yes' />    "
    "<tag k='highway' v='path' />    <tag k='surface' v='gravel' />    <tag "
    "k='trail_visibility' v='excellent' />  </way></osm>";

// Map
Map osmMap;

void setup() {
  Serial.begin(115200);

  // Init map
  osmMap.begin(true);
}

void loop() {
  // Parse
  osmMap.parse(osmString);
  delay(3000);
}

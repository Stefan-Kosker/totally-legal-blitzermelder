<?php
/**
 * Created by PhpStorm.
 * User: ry74
 * Date: 03.04.18
 * Time: 00:38
 */

$de_x_min = 5;
$de_x_max = 15;
$de_y_min = 47;
$de_y_max = 55;
$GLOBALS['notFound'] = 0;
$GLOBALS['scrappedBlitzerArray'] = [];
$increment = 0.5;

for ($x = $de_x_min; $x < $de_x_max; $x += $increment) {
    for ($y = $de_y_min; $y < $de_y_max; $y += $increment) {
        getBlitzer($x, $y, $increment);
    }
}
writeBlitzerInCsvFile();
$amountSectors = (abs($de_x_max - $de_x_min) / $increment) * (abs($de_y_max - $de_y_min) / $increment);
echo 'Not Found in ' . $GLOBALS['notFound'] . ' sectors out of ' . $amountSectors;

/**
 * @param double $x
 * @param double $y
 * @param $increment
 * @return array|string
 */
function getBlitzer($x, $y, $increment)
{
    $url = buildUrl($x, $y, $increment);
    $xmlString = file_get_contents($url);
    if (strpos($xmlString, 'anzahl') === false) {
        parseXml($xmlString);
    } else {
        if (strpos($xmlString, 'anzahl="0"') === false) {
            echo $x . " " . $y . " too much\n";
        } else {
            $GLOBALS['notFound'] += 1;
        }
    }
}

function writeBlitzerInCsvFile()
{
    $counter = 0;
    $counterLimit = sizeof($GLOBALS['scrappedBlitzerArray']) / 3;

    $file = fopen('RadarPositions.h', 'w+');
    fwrite($file, "#define PROGMEM_LATE __attribute__((section(\"progmem.zzz\")))\n\n");
    fwrite($file, "const float radarPositions1[][3] PROGMEM_LATE = {\n");


    foreach ($GLOBALS['scrappedBlitzerArray'] as $key => $value) {

        if ($value !== null) {
            $line = "{" . $value['long'] . ',' . $value['lat'] . ',' . $value['speed'] . "},\n";
            fwrite($file, $line);
        }
        unset($GLOBALS['scrappedBlitzerArray'][$key]);
        if ($counter > $counterLimit){
            break;
        }
        $counter++;
    }
    $counter = 0;
    fwrite($file, "};\n const float radarPositions2[][3] PROGMEM_LATE = {\n");

    foreach ($GLOBALS['scrappedBlitzerArray'] as $key => $value) {
        if ($value !== null) {
            $line = "{" . $value['long'] . ',' . $value['lat'] . ',' . $value['speed'] . "},\n";
            fwrite($file, $line);
        }
        unset($GLOBALS['scrappedBlitzerArray'][$key]);
        if ($counter > $counterLimit){
            break;
        }
        $counter++;
    }
    fwrite($file, "};\n const float radarPositions3[][3] PROGMEM_LATE = {\n");

    foreach ($GLOBALS['scrappedBlitzerArray'] as $key => $value) {
        if ($value !== null) {
            $line = "{" . $value['long'] . ',' . $value['lat'] . ',' . $value['speed'] . "},\n";
            fwrite($file, $line);
        }
        unset($GLOBALS['scrappedBlitzerArray'][$key]);
    }
    fwrite($file, "};");

    fclose($file);
}

/**
 * @param double $x
 * @param double $y
 * @return string
 */
function buildUrl($x, $y, $increment)
{
    $url = 'https://map.scdb.info/speedcameramap/xhr/search/l/de-DE/lngmin/' . $x . '/lngmax/' . ($x + 0.5) . '/latmin/' . $y . '/latmax/' . ($y + 0.5);
    return $url;
}

/**
 * @param string $xmlString
 */
function parseXml($xmlString)
{
    $blitzerList = new SimpleXMLElement($xmlString);

    foreach ($blitzerList->marker as $blitzerEintrag) {
        $id = $blitzerEintrag->attributes()->id->__toString();
        $type = $blitzerEintrag->attributes()->rawType->__toString();
        if ($type === 'G' || $type === 'GA') {
            if (!key_exists($id, $GLOBALS['scrappedBlitzerArray'])) {
                $GLOBALS['scrappedBlitzerArray'][$id] = [];
                $GLOBALS['scrappedBlitzerArray'][$id]['long'] = $blitzerEintrag->attributes()->lng->__toString();
                $GLOBALS['scrappedBlitzerArray'][$id]['lat'] = $blitzerEintrag->attributes()->lat->__toString();
                $GLOBALS['scrappedBlitzerArray'][$id]['speed'] = $blitzerEintrag->attributes()->speed->__toString();
            }
        }
    }
}

//https://map.scdb.info/speedcameramap/xhr/search/l/de-DE/lngmin/9/lngmax/10/latmin/48/latmax/49

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
    $file = fopen('blitzerList.csv', 'w+');
    foreach ($GLOBALS['scrappedBlitzerArray'] as $value) {
        if ($value !== null) {
            $line = $value['long'] . ',' . $value['let'] . ',' . $value['speed'] . ";\n";
            fwrite($file,  $line);
        }
    }
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
        if (!key_exists($id, $GLOBALS['scrappedBlitzerArray'])) {
            $GLOBALS['scrappedBlitzerArray'][$id] = [];
            $GLOBALS['scrappedBlitzerArray'][$id]['long'] = $blitzerEintrag->attributes()->lng->__toString();
            $GLOBALS['scrappedBlitzerArray'][$id]['lat'] = $blitzerEintrag->attributes()->lat->__toString();
            $GLOBALS['scrappedBlitzerArray'][$id]['speed'] = $blitzerEintrag->attributes()->speed->__toString();
        }
    }
}

//https://map.scdb.info/speedcameramap/xhr/search/l/de-DE/lngmin/9/lngmax/10/latmin/48/latmax/49
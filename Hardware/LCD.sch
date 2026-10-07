<?xml version="1.0" encoding="utf-8"?>
<!DOCTYPE eagle SYSTEM "eagle.dtd">
<eagle version="6.4">
<drawing>
<settings>
<setting alwaysvectorfont="no"/>
<setting verticaltext="up"/>
</settings>
<grid distance="0.1" unitdist="inch" unit="inch" style="lines" multiple="1" display="no" altdistance="0.01" altunitdist="inch" altunit="inch"/>
<layers>
<layer number="1" name="Top" color="4" fill="1" visible="no" active="no"/>
<layer number="16" name="Bottom" color="1" fill="1" visible="no" active="no"/>
<layer number="17" name="Pads" color="2" fill="1" visible="no" active="no"/>
<layer number="18" name="Vias" color="2" fill="1" visible="no" active="no"/>
<layer number="19" name="Unrouted" color="6" fill="1" visible="no" active="no"/>
<layer number="20" name="Dimension" color="15" fill="1" visible="no" active="no"/>
<layer number="21" name="tPlace" color="7" fill="1" visible="no" active="no"/>
<layer number="22" name="bPlace" color="7" fill="1" visible="no" active="no"/>
<layer number="23" name="tOrigins" color="15" fill="1" visible="no" active="no"/>
<layer number="24" name="bOrigins" color="15" fill="1" visible="no" active="no"/>
<layer number="25" name="tNames" color="7" fill="1" visible="no" active="no"/>
<layer number="26" name="bNames" color="7" fill="1" visible="no" active="no"/>
<layer number="27" name="tValues" color="7" fill="1" visible="no" active="no"/>
<layer number="28" name="bValues" color="7" fill="1" visible="no" active="no"/>
<layer number="29" name="tStop" color="7" fill="3" visible="no" active="no"/>
<layer number="30" name="bStop" color="7" fill="6" visible="no" active="no"/>
<layer number="31" name="tCream" color="7" fill="4" visible="no" active="no"/>
<layer number="32" name="bCream" color="7" fill="5" visible="no" active="no"/>
<layer number="33" name="tFinish" color="6" fill="3" visible="no" active="no"/>
<layer number="34" name="bFinish" color="6" fill="6" visible="no" active="no"/>
<layer number="35" name="tGlue" color="7" fill="4" visible="no" active="no"/>
<layer number="36" name="bGlue" color="7" fill="5" visible="no" active="no"/>
<layer number="37" name="tTest" color="7" fill="1" visible="no" active="no"/>
<layer number="38" name="bTest" color="7" fill="1" visible="no" active="no"/>
<layer number="39" name="tKeepout" color="4" fill="11" visible="no" active="no"/>
<layer number="40" name="bKeepout" color="1" fill="11" visible="no" active="no"/>
<layer number="41" name="tRestrict" color="4" fill="10" visible="no" active="no"/>
<layer number="42" name="bRestrict" color="1" fill="10" visible="no" active="no"/>
<layer number="43" name="vRestrict" color="2" fill="10" visible="no" active="no"/>
<layer number="44" name="Drills" color="7" fill="1" visible="no" active="no"/>
<layer number="45" name="Holes" color="7" fill="1" visible="no" active="no"/>
<layer number="46" name="Milling" color="3" fill="1" visible="no" active="no"/>
<layer number="47" name="Measures" color="7" fill="1" visible="no" active="no"/>
<layer number="48" name="Document" color="7" fill="1" visible="no" active="no"/>
<layer number="49" name="Reference" color="7" fill="1" visible="no" active="no"/>
<layer number="51" name="tDocu" color="7" fill="1" visible="no" active="no"/>
<layer number="52" name="bDocu" color="7" fill="1" visible="no" active="no"/>
<layer number="91" name="Nets" color="2" fill="1" visible="yes" active="yes"/>
<layer number="92" name="Busses" color="1" fill="1" visible="yes" active="yes"/>
<layer number="93" name="Pins" color="2" fill="1" visible="no" active="yes"/>
<layer number="94" name="Symbols" color="4" fill="1" visible="yes" active="yes"/>
<layer number="95" name="Names" color="7" fill="1" visible="yes" active="yes"/>
<layer number="96" name="Values" color="7" fill="1" visible="yes" active="yes"/>
<layer number="97" name="Info" color="7" fill="1" visible="yes" active="yes"/>
<layer number="98" name="Guide" color="6" fill="1" visible="yes" active="yes"/>
</layers>
<schematic xreflabel="%F%N/%S.%C%R" xrefpart="/%S.%C%R">
<libraries>
<library name="display-lcd">
<description>&lt;b&gt;Hitachi, Data Modul, Tuxgraphics - LCD Displays&lt;/b&gt;&lt;p&gt;
&lt;author&gt;Created by librarian@cadsoft.de&lt;/author&gt;</description>
<packages>
<package name="TUXGR_20X2">
<description>&lt;b&gt;Tuxgraphics LCD display 20x2 characters&lt;/b&gt; reflective, without background light&lt;p&gt;
Source: tuxgr_20x2.pdf</description>
<wire x1="-57.9" y1="18.4" x2="57.9" y2="18.4" width="0.2032" layer="21"/>
<wire x1="57.9" y1="18.4" x2="57.9" y2="-18.4" width="0.2032" layer="21"/>
<wire x1="57.9" y1="-18.4" x2="-57.9" y2="-18.4" width="0.2032" layer="21"/>
<wire x1="-57.9" y1="-18.4" x2="-57.9" y2="18.4" width="0.2032" layer="21"/>
<wire x1="-40.4" y1="9.15" x2="42.4" y2="9.15" width="0.2032" layer="21"/>
<wire x1="42.4" y1="9.15" x2="42.4" y2="-9.15" width="0.2032" layer="21"/>
<wire x1="42.4" y1="-9.15" x2="-40.4" y2="-9.15" width="0.2032" layer="21"/>
<wire x1="-40.4" y1="-9.15" x2="-40.4" y2="9.15" width="0.2032" layer="21"/>
<wire x1="-44.5" y1="15.5" x2="46.5" y2="15.5" width="0.2032" layer="21"/>
<wire x1="46.5" y1="15.5" x2="46.5" y2="-15.5" width="0.2032" layer="21"/>
<wire x1="46.5" y1="-15.5" x2="-44.5" y2="-15.5" width="0.2032" layer="21"/>
<wire x1="-44.5" y1="-15.5" x2="-44.5" y2="15.5" width="0.2032" layer="21"/>
<pad name="1" x="-52.73" y="-7.62" drill="1" diameter="1.6764"/>
<pad name="2" x="-55.27" y="-7.62" drill="1" diameter="1.6764"/>
<pad name="3" x="-52.73" y="-5.08" drill="1" diameter="1.6764"/>
<pad name="4" x="-55.27" y="-5.08" drill="1" diameter="1.6764"/>
<pad name="5" x="-52.73" y="-2.54" drill="1" diameter="1.6764"/>
<pad name="6" x="-55.27" y="-2.54" drill="1" diameter="1.6764"/>
<pad name="7" x="-52.73" y="0" drill="1" diameter="1.6764"/>
<pad name="8" x="-55.27" y="0" drill="1" diameter="1.6764"/>
<pad name="9" x="-52.73" y="2.54" drill="1" diameter="1.6764"/>
<pad name="10" x="-55.27" y="2.54" drill="1" diameter="1.6764"/>
<pad name="11" x="-52.73" y="5.08" drill="1" diameter="1.6764"/>
<pad name="12" x="-55.27" y="5.08" drill="1" diameter="1.6764"/>
<pad name="13" x="-52.73" y="7.62" drill="1" diameter="1.6764"/>
<pad name="14" x="-55.27" y="7.62" drill="1" diameter="1.6764"/>
<pad name="15" x="-52.73" y="10.16" drill="1" diameter="1.6764"/>
<pad name="16" x="-55.27" y="10.16" drill="1" diameter="1.6764"/>
<text x="-53.34" y="-20.32" size="1.27" layer="25">&gt;NAME</text>
<text x="-43.18" y="-20.32" size="1.27" layer="27">&gt;VALUE</text>
<rectangle x1="-35.75" y1="0.2" x2="-32.55" y2="5.75" layer="21"/>
<rectangle x1="-35.75" y1="-5.75" x2="-32.55" y2="-0.2" layer="21"/>
<rectangle x1="-32.05" y1="0.2" x2="-28.85" y2="5.75" layer="21"/>
<rectangle x1="-32.05" y1="-5.75" x2="-28.85" y2="-0.2" layer="21"/>
<rectangle x1="-28.35" y1="0.2" x2="-25.15" y2="5.75" layer="21"/>
<rectangle x1="-28.35" y1="-5.75" x2="-25.15" y2="-0.2" layer="21"/>
<rectangle x1="-24.65" y1="0.2" x2="-21.45" y2="5.75" layer="21"/>
<rectangle x1="-24.65" y1="-5.75" x2="-21.45" y2="-0.2" layer="21"/>
<rectangle x1="-20.95" y1="0.2" x2="-17.75" y2="5.75" layer="21"/>
<rectangle x1="-20.95" y1="-5.75" x2="-17.75" y2="-0.2" layer="21"/>
<rectangle x1="-17.25" y1="0.2" x2="-14.05" y2="5.75" layer="21"/>
<rectangle x1="-17.25" y1="-5.75" x2="-14.05" y2="-0.2" layer="21"/>
<rectangle x1="-13.55" y1="0.2" x2="-10.35" y2="5.75" layer="21"/>
<rectangle x1="-13.55" y1="-5.75" x2="-10.35" y2="-0.2" layer="21"/>
<rectangle x1="-9.85" y1="0.2" x2="-6.65" y2="5.75" layer="21"/>
<rectangle x1="-9.85" y1="-5.75" x2="-6.65" y2="-0.2" layer="21"/>
<rectangle x1="-6.15" y1="0.2" x2="-2.95" y2="5.75" layer="21"/>
<rectangle x1="-6.15" y1="-5.75" x2="-2.95" y2="-0.2" layer="21"/>
<rectangle x1="-2.45" y1="0.2" x2="0.75" y2="5.75" layer="21"/>
<rectangle x1="-2.45" y1="-5.75" x2="0.75" y2="-0.2" layer="21"/>
<rectangle x1="1.25" y1="0.2" x2="4.45" y2="5.75" layer="21"/>
<rectangle x1="1.25" y1="-5.75" x2="4.45" y2="-0.2" layer="21"/>
<rectangle x1="4.95" y1="0.2" x2="8.15" y2="5.75" layer="21"/>
<rectangle x1="4.95" y1="-5.75" x2="8.15" y2="-0.2" layer="21"/>
<rectangle x1="8.65" y1="0.2" x2="11.85" y2="5.75" layer="21"/>
<rectangle x1="8.65" y1="-5.75" x2="11.85" y2="-0.2" layer="21"/>
<rectangle x1="12.35" y1="0.2" x2="15.55" y2="5.75" layer="21"/>
<rectangle x1="12.35" y1="-5.75" x2="15.55" y2="-0.2" layer="21"/>
<rectangle x1="16.05" y1="0.2" x2="19.25" y2="5.75" layer="21"/>
<rectangle x1="16.05" y1="-5.75" x2="19.25" y2="-0.2" layer="21"/>
<rectangle x1="19.75" y1="0.2" x2="22.95" y2="5.75" layer="21"/>
<rectangle x1="19.75" y1="-5.75" x2="22.95" y2="-0.2" layer="21"/>
<rectangle x1="23.45" y1="0.2" x2="26.65" y2="5.75" layer="21"/>
<rectangle x1="23.45" y1="-5.75" x2="26.65" y2="-0.2" layer="21"/>
<rectangle x1="27.15" y1="0.2" x2="30.35" y2="5.75" layer="21"/>
<rectangle x1="27.15" y1="-5.75" x2="30.35" y2="-0.2" layer="21"/>
<rectangle x1="30.85" y1="0.2" x2="34.05" y2="5.75" layer="21"/>
<rectangle x1="30.85" y1="-5.75" x2="34.05" y2="-0.2" layer="21"/>
<rectangle x1="34.55" y1="0.2" x2="37.75" y2="5.75" layer="21"/>
<rectangle x1="34.55" y1="-5.75" x2="37.75" y2="-0.2" layer="21"/>
<hole x="-54" y="-14.5" drill="3.5"/>
<hole x="54" y="-14.5" drill="3.5"/>
<hole x="-54" y="14.5" drill="3.5"/>
<hole x="54" y="14.5" drill="3.5"/>
</package>
</packages>
<symbols>
<symbol name="TUXGR_20X2">
<wire x1="-26.67" y1="-7.62" x2="26.67" y2="-7.62" width="0.2032" layer="94"/>
<wire x1="26.67" y1="-7.62" x2="26.67" y2="12.7" width="0.2032" layer="94"/>
<wire x1="26.67" y1="12.7" x2="-26.67" y2="12.7" width="0.2032" layer="94"/>
<wire x1="-26.67" y1="12.7" x2="-26.67" y2="-7.62" width="0.2032" layer="94"/>
<text x="-17.78" y="10.668" size="1.524" layer="94">LCD DISPLAY 20x2</text>
<text x="-25.4" y="13.97" size="1.778" layer="95">&gt;NAME</text>
<text x="-10.16" y="13.97" size="1.778" layer="96">&gt;VALUE</text>
<rectangle x1="-25.4" y1="6.604" x2="-23.114" y2="10.16" layer="94"/>
<rectangle x1="-25.4" y1="2.54" x2="-23.114" y2="6.096" layer="94"/>
<rectangle x1="-22.86" y1="6.604" x2="-20.574" y2="10.16" layer="94"/>
<rectangle x1="-22.86" y1="2.54" x2="-20.574" y2="6.096" layer="94"/>
<rectangle x1="-20.32" y1="6.604" x2="-18.034" y2="10.16" layer="94"/>
<rectangle x1="-20.32" y1="2.54" x2="-18.034" y2="6.096" layer="94"/>
<rectangle x1="-17.78" y1="6.604" x2="-15.494" y2="10.16" layer="94"/>
<rectangle x1="-17.78" y1="2.54" x2="-15.494" y2="6.096" layer="94"/>
<rectangle x1="-15.24" y1="6.604" x2="-12.954" y2="10.16" layer="94"/>
<rectangle x1="-15.24" y1="2.54" x2="-12.954" y2="6.096" layer="94"/>
<rectangle x1="-12.7" y1="6.604" x2="-10.414" y2="10.16" layer="94"/>
<rectangle x1="-12.7" y1="2.54" x2="-10.414" y2="6.096" layer="94"/>
<rectangle x1="-10.16" y1="6.604" x2="-7.874" y2="10.16" layer="94"/>
<rectangle x1="-10.16" y1="2.54" x2="-7.874" y2="6.096" layer="94"/>
<rectangle x1="-7.62" y1="6.604" x2="-5.334" y2="10.16" layer="94"/>
<rectangle x1="-7.62" y1="2.54" x2="-5.334" y2="6.096" layer="94"/>
<rectangle x1="-5.08" y1="6.604" x2="-2.794" y2="10.16" layer="94"/>
<rectangle x1="-5.08" y1="2.54" x2="-2.794" y2="6.096" layer="94"/>
<rectangle x1="-2.54" y1="6.604" x2="-0.254" y2="10.16" layer="94"/>
<rectangle x1="-2.54" y1="2.54" x2="-0.254" y2="6.096" layer="94"/>
<rectangle x1="0" y1="6.604" x2="2.286" y2="10.16" layer="94"/>
<rectangle x1="0" y1="2.54" x2="2.286" y2="6.096" layer="94"/>
<rectangle x1="2.54" y1="6.604" x2="4.826" y2="10.16" layer="94"/>
<rectangle x1="2.54" y1="2.54" x2="4.826" y2="6.096" layer="94"/>
<rectangle x1="5.08" y1="6.604" x2="7.366" y2="10.16" layer="94"/>
<rectangle x1="5.08" y1="2.54" x2="7.366" y2="6.096" layer="94"/>
<rectangle x1="7.62" y1="6.604" x2="9.906" y2="10.16" layer="94"/>
<rectangle x1="7.62" y1="2.54" x2="9.906" y2="6.096" layer="94"/>
<rectangle x1="10.16" y1="6.604" x2="12.446" y2="10.16" layer="94"/>
<rectangle x1="10.16" y1="2.54" x2="12.446" y2="6.096" layer="94"/>
<rectangle x1="12.7" y1="6.604" x2="14.986" y2="10.16" layer="94"/>
<rectangle x1="12.7" y1="2.54" x2="14.986" y2="6.096" layer="94"/>
<rectangle x1="15.24" y1="6.604" x2="17.526" y2="10.16" layer="94"/>
<rectangle x1="15.24" y1="2.54" x2="17.526" y2="6.096" layer="94"/>
<rectangle x1="17.78" y1="6.604" x2="20.066" y2="10.16" layer="94"/>
<rectangle x1="17.78" y1="2.54" x2="20.066" y2="6.096" layer="94"/>
<rectangle x1="20.32" y1="6.604" x2="22.606" y2="10.16" layer="94"/>
<rectangle x1="20.32" y1="2.54" x2="22.606" y2="6.096" layer="94"/>
<rectangle x1="22.86" y1="6.604" x2="25.146" y2="10.16" layer="94"/>
<rectangle x1="22.86" y1="2.54" x2="25.146" y2="6.096" layer="94"/>
<pin name="GND" x="-22.86" y="-10.16" length="short" direction="pwr" rot="R90"/>
<pin name="VCC" x="-20.32" y="-10.16" length="short" direction="pwr" rot="R90"/>
<pin name="CONTR" x="-17.78" y="-10.16" length="short" direction="in" rot="R90"/>
<pin name="RS" x="-15.24" y="-10.16" length="short" direction="in" rot="R90"/>
<pin name="R/W" x="-12.7" y="-10.16" length="short" direction="in" rot="R90"/>
<pin name="E" x="-10.16" y="-10.16" length="short" direction="in" rot="R90"/>
<pin name="D0" x="-7.62" y="-10.16" length="short" direction="in" rot="R90"/>
<pin name="D1" x="-5.08" y="-10.16" length="short" direction="in" rot="R90"/>
<pin name="D2" x="-2.54" y="-10.16" length="short" direction="in" rot="R90"/>
<pin name="D3" x="0" y="-10.16" length="short" direction="in" rot="R90"/>
<pin name="D4" x="2.54" y="-10.16" length="short" direction="in" rot="R90"/>
<pin name="D5" x="5.08" y="-10.16" length="short" direction="in" rot="R90"/>
<pin name="D6" x="7.62" y="-10.16" length="short" direction="in" rot="R90"/>
<pin name="D7" x="10.16" y="-10.16" length="short" direction="in" rot="R90"/>
<pin name="NC@1" x="12.7" y="-10.16" length="short" direction="nc" rot="R90"/>
<pin name="NC@2" x="15.24" y="-10.16" length="short" direction="nc" rot="R90"/>
</symbol>
</symbols>
<devicesets>
<deviceset name="TUXGR_20X2" prefix="DIS">
<description>&lt;b&gt;Tuxgraphics LCD display 20x2 characters&lt;/b&gt; reflective, without background light&lt;p&gt;
Source: tuxgr_20x2.pdf</description>
<gates>
<gate name="G$1" symbol="TUXGR_20X2" x="0" y="0"/>
</gates>
<devices>
<device name="" package="TUXGR_20X2">
<connects>
<connect gate="G$1" pin="CONTR" pad="3"/>
<connect gate="G$1" pin="D0" pad="7"/>
<connect gate="G$1" pin="D1" pad="8"/>
<connect gate="G$1" pin="D2" pad="9"/>
<connect gate="G$1" pin="D3" pad="10"/>
<connect gate="G$1" pin="D4" pad="11"/>
<connect gate="G$1" pin="D5" pad="12"/>
<connect gate="G$1" pin="D6" pad="13"/>
<connect gate="G$1" pin="D7" pad="14"/>
<connect gate="G$1" pin="E" pad="6"/>
<connect gate="G$1" pin="GND" pad="1"/>
<connect gate="G$1" pin="NC@1" pad="15"/>
<connect gate="G$1" pin="NC@2" pad="16"/>
<connect gate="G$1" pin="R/W" pad="5"/>
<connect gate="G$1" pin="RS" pad="4"/>
<connect gate="G$1" pin="VCC" pad="2"/>
</connects>
<technologies>
<technology name="">
<attribute name="MF" value="" constant="no"/>
<attribute name="MPN" value="" constant="no"/>
<attribute name="OC_FARNELL" value="unknown" constant="no"/>
<attribute name="OC_NEWARK" value="unknown" constant="no"/>
</technology>
</technologies>
</device>
</devices>
</deviceset>
</devicesets>
</library>
<library name="wirepad">
<description>&lt;b&gt;Single Pads&lt;/b&gt;&lt;p&gt;
&lt;author&gt;Created by librarian@cadsoft.de&lt;/author&gt;</description>
<packages>
<package name="1,6/0,9">
<description>&lt;b&gt;THROUGH-HOLE PAD&lt;/b&gt;</description>
<wire x1="-0.508" y1="0.762" x2="-0.762" y2="0.762" width="0.1524" layer="21"/>
<wire x1="-0.762" y1="0.762" x2="-0.762" y2="0.508" width="0.1524" layer="21"/>
<wire x1="-0.762" y1="-0.508" x2="-0.762" y2="-0.762" width="0.1524" layer="21"/>
<wire x1="-0.762" y1="-0.762" x2="-0.508" y2="-0.762" width="0.1524" layer="21"/>
<wire x1="0.508" y1="-0.762" x2="0.762" y2="-0.762" width="0.1524" layer="21"/>
<wire x1="0.762" y1="-0.762" x2="0.762" y2="-0.508" width="0.1524" layer="21"/>
<wire x1="0.762" y1="0.508" x2="0.762" y2="0.762" width="0.1524" layer="21"/>
<wire x1="0.762" y1="0.762" x2="0.508" y2="0.762" width="0.1524" layer="21"/>
<circle x="0" y="0" radius="0.635" width="0.1524" layer="51"/>
<pad name="1" x="0" y="0" drill="0.9144" diameter="1.6002" shape="octagon"/>
<text x="-0.762" y="1.016" size="1.27" layer="25" ratio="10">&gt;NAME</text>
<text x="0" y="0.6" size="0.0254" layer="27">&gt;VALUE</text>
</package>
</packages>
<symbols>
<symbol name="PAD">
<wire x1="-1.016" y1="1.016" x2="1.016" y2="-1.016" width="0.254" layer="94"/>
<wire x1="-1.016" y1="-1.016" x2="1.016" y2="1.016" width="0.254" layer="94"/>
<text x="-1.143" y="1.8542" size="1.778" layer="95">&gt;NAME</text>
<text x="-1.143" y="-3.302" size="1.778" layer="96">&gt;VALUE</text>
<pin name="P" x="2.54" y="0" visible="off" length="short" direction="pas" rot="R180"/>
</symbol>
</symbols>
<devicesets>
<deviceset name="1,6/0,9" prefix="PAD" uservalue="yes">
<description>&lt;b&gt;THROUGH-HOLE PAD&lt;/b&gt;</description>
<gates>
<gate name="1" symbol="PAD" x="0" y="0"/>
</gates>
<devices>
<device name="" package="1,6/0,9">
<connects>
<connect gate="1" pin="P" pad="1"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
</devicesets>
</library>
<library name="pinhead">
<description>&lt;b&gt;Pin Header Connectors&lt;/b&gt;&lt;p&gt;
&lt;author&gt;Created by librarian@cadsoft.de&lt;/author&gt;</description>
<packages>
<package name="2X08">
<description>&lt;b&gt;PIN HEADER&lt;/b&gt;</description>
<wire x1="-10.16" y1="-1.905" x2="-9.525" y2="-2.54" width="0.1524" layer="21"/>
<wire x1="-8.255" y1="-2.54" x2="-7.62" y2="-1.905" width="0.1524" layer="21"/>
<wire x1="-7.62" y1="-1.905" x2="-6.985" y2="-2.54" width="0.1524" layer="21"/>
<wire x1="-5.715" y1="-2.54" x2="-5.08" y2="-1.905" width="0.1524" layer="21"/>
<wire x1="-5.08" y1="-1.905" x2="-4.445" y2="-2.54" width="0.1524" layer="21"/>
<wire x1="-3.175" y1="-2.54" x2="-2.54" y2="-1.905" width="0.1524" layer="21"/>
<wire x1="-2.54" y1="-1.905" x2="-1.905" y2="-2.54" width="0.1524" layer="21"/>
<wire x1="-0.635" y1="-2.54" x2="0" y2="-1.905" width="0.1524" layer="21"/>
<wire x1="0" y1="-1.905" x2="0.635" y2="-2.54" width="0.1524" layer="21"/>
<wire x1="1.905" y1="-2.54" x2="2.54" y2="-1.905" width="0.1524" layer="21"/>
<wire x1="2.54" y1="-1.905" x2="3.175" y2="-2.54" width="0.1524" layer="21"/>
<wire x1="4.445" y1="-2.54" x2="5.08" y2="-1.905" width="0.1524" layer="21"/>
<wire x1="-10.16" y1="-1.905" x2="-10.16" y2="1.905" width="0.1524" layer="21"/>
<wire x1="-10.16" y1="1.905" x2="-9.525" y2="2.54" width="0.1524" layer="21"/>
<wire x1="-9.525" y1="2.54" x2="-8.255" y2="2.54" width="0.1524" layer="21"/>
<wire x1="-8.255" y1="2.54" x2="-7.62" y2="1.905" width="0.1524" layer="21"/>
<wire x1="-7.62" y1="1.905" x2="-6.985" y2="2.54" width="0.1524" layer="21"/>
<wire x1="-6.985" y1="2.54" x2="-5.715" y2="2.54" width="0.1524" layer="21"/>
<wire x1="-5.715" y1="2.54" x2="-5.08" y2="1.905" width="0.1524" layer="21"/>
<wire x1="-5.08" y1="1.905" x2="-4.445" y2="2.54" width="0.1524" layer="21"/>
<wire x1="-4.445" y1="2.54" x2="-3.175" y2="2.54" width="0.1524" layer="21"/>
<wire x1="-3.175" y1="2.54" x2="-2.54" y2="1.905" width="0.1524" layer="21"/>
<wire x1="-2.54" y1="1.905" x2="-1.905" y2="2.54" width="0.1524" layer="21"/>
<wire x1="-1.905" y1="2.54" x2="-0.635" y2="2.54" width="0.1524" layer="21"/>
<wire x1="-0.635" y1="2.54" x2="0" y2="1.905" width="0.1524" layer="21"/>
<wire x1="0" y1="1.905" x2="0.635" y2="2.54" width="0.1524" layer="21"/>
<wire x1="0.635" y1="2.54" x2="1.905" y2="2.54" width="0.1524" layer="21"/>
<wire x1="1.905" y1="2.54" x2="2.54" y2="1.905" width="0.1524" layer="21"/>
<wire x1="2.54" y1="1.905" x2="3.175" y2="2.54" width="0.1524" layer="21"/>
<wire x1="3.175" y1="2.54" x2="4.445" y2="2.54" width="0.1524" layer="21"/>
<wire x1="4.445" y1="2.54" x2="5.08" y2="1.905" width="0.1524" layer="21"/>
<wire x1="5.08" y1="1.905" x2="5.715" y2="2.54" width="0.1524" layer="21"/>
<wire x1="5.715" y1="2.54" x2="6.985" y2="2.54" width="0.1524" layer="21"/>
<wire x1="6.985" y1="2.54" x2="7.62" y2="1.905" width="0.1524" layer="21"/>
<wire x1="7.62" y1="-1.905" x2="6.985" y2="-2.54" width="0.1524" layer="21"/>
<wire x1="5.08" y1="-1.905" x2="5.715" y2="-2.54" width="0.1524" layer="21"/>
<wire x1="-7.62" y1="1.905" x2="-7.62" y2="-1.905" width="0.1524" layer="21"/>
<wire x1="-5.08" y1="1.905" x2="-5.08" y2="-1.905" width="0.1524" layer="21"/>
<wire x1="-2.54" y1="1.905" x2="-2.54" y2="-1.905" width="0.1524" layer="21"/>
<wire x1="0" y1="1.905" x2="0" y2="-1.905" width="0.1524" layer="21"/>
<wire x1="2.54" y1="1.905" x2="2.54" y2="-1.905" width="0.1524" layer="21"/>
<wire x1="5.08" y1="1.905" x2="5.08" y2="-1.905" width="0.1524" layer="21"/>
<wire x1="7.62" y1="1.905" x2="7.62" y2="-1.905" width="0.1524" layer="21"/>
<wire x1="5.715" y1="-2.54" x2="6.985" y2="-2.54" width="0.1524" layer="21"/>
<wire x1="3.175" y1="-2.54" x2="4.445" y2="-2.54" width="0.1524" layer="21"/>
<wire x1="0.635" y1="-2.54" x2="1.905" y2="-2.54" width="0.1524" layer="21"/>
<wire x1="-1.905" y1="-2.54" x2="-0.635" y2="-2.54" width="0.1524" layer="21"/>
<wire x1="-4.445" y1="-2.54" x2="-3.175" y2="-2.54" width="0.1524" layer="21"/>
<wire x1="-6.985" y1="-2.54" x2="-5.715" y2="-2.54" width="0.1524" layer="21"/>
<wire x1="-9.525" y1="-2.54" x2="-8.255" y2="-2.54" width="0.1524" layer="21"/>
<wire x1="7.62" y1="1.905" x2="8.255" y2="2.54" width="0.1524" layer="21"/>
<wire x1="8.255" y1="2.54" x2="9.525" y2="2.54" width="0.1524" layer="21"/>
<wire x1="9.525" y1="2.54" x2="10.16" y2="1.905" width="0.1524" layer="21"/>
<wire x1="10.16" y1="-1.905" x2="9.525" y2="-2.54" width="0.1524" layer="21"/>
<wire x1="7.62" y1="-1.905" x2="8.255" y2="-2.54" width="0.1524" layer="21"/>
<wire x1="10.16" y1="1.905" x2="10.16" y2="-1.905" width="0.1524" layer="21"/>
<wire x1="8.255" y1="-2.54" x2="9.525" y2="-2.54" width="0.1524" layer="21"/>
<pad name="1" x="-8.89" y="-1.27" drill="1.016" shape="octagon"/>
<pad name="2" x="-8.89" y="1.27" drill="1.016" shape="octagon"/>
<pad name="3" x="-6.35" y="-1.27" drill="1.016" shape="octagon"/>
<pad name="4" x="-6.35" y="1.27" drill="1.016" shape="octagon"/>
<pad name="5" x="-3.81" y="-1.27" drill="1.016" shape="octagon"/>
<pad name="6" x="-3.81" y="1.27" drill="1.016" shape="octagon"/>
<pad name="7" x="-1.27" y="-1.27" drill="1.016" shape="octagon"/>
<pad name="8" x="-1.27" y="1.27" drill="1.016" shape="octagon"/>
<pad name="9" x="1.27" y="-1.27" drill="1.016" shape="octagon"/>
<pad name="10" x="1.27" y="1.27" drill="1.016" shape="octagon"/>
<pad name="11" x="3.81" y="-1.27" drill="1.016" shape="octagon"/>
<pad name="12" x="3.81" y="1.27" drill="1.016" shape="octagon"/>
<pad name="13" x="6.35" y="-1.27" drill="1.016" shape="octagon"/>
<pad name="14" x="6.35" y="1.27" drill="1.016" shape="octagon"/>
<pad name="15" x="8.89" y="-1.27" drill="1.016" shape="octagon"/>
<pad name="16" x="8.89" y="1.27" drill="1.016" shape="octagon"/>
<text x="-10.16" y="3.175" size="1.27" layer="25" ratio="10">&gt;NAME</text>
<text x="-10.16" y="-4.445" size="1.27" layer="27">&gt;VALUE</text>
<rectangle x1="-9.144" y1="-1.524" x2="-8.636" y2="-1.016" layer="51"/>
<rectangle x1="-9.144" y1="1.016" x2="-8.636" y2="1.524" layer="51"/>
<rectangle x1="-6.604" y1="1.016" x2="-6.096" y2="1.524" layer="51"/>
<rectangle x1="-6.604" y1="-1.524" x2="-6.096" y2="-1.016" layer="51"/>
<rectangle x1="-4.064" y1="1.016" x2="-3.556" y2="1.524" layer="51"/>
<rectangle x1="-4.064" y1="-1.524" x2="-3.556" y2="-1.016" layer="51"/>
<rectangle x1="-1.524" y1="1.016" x2="-1.016" y2="1.524" layer="51"/>
<rectangle x1="1.016" y1="1.016" x2="1.524" y2="1.524" layer="51"/>
<rectangle x1="3.556" y1="1.016" x2="4.064" y2="1.524" layer="51"/>
<rectangle x1="-1.524" y1="-1.524" x2="-1.016" y2="-1.016" layer="51"/>
<rectangle x1="1.016" y1="-1.524" x2="1.524" y2="-1.016" layer="51"/>
<rectangle x1="3.556" y1="-1.524" x2="4.064" y2="-1.016" layer="51"/>
<rectangle x1="6.096" y1="1.016" x2="6.604" y2="1.524" layer="51"/>
<rectangle x1="6.096" y1="-1.524" x2="6.604" y2="-1.016" layer="51"/>
<rectangle x1="8.636" y1="1.016" x2="9.144" y2="1.524" layer="51"/>
<rectangle x1="8.636" y1="-1.524" x2="9.144" y2="-1.016" layer="51"/>
</package>
<package name="2X08/90">
<description>&lt;b&gt;PIN HEADER&lt;/b&gt;</description>
<wire x1="-10.16" y1="-1.905" x2="-7.62" y2="-1.905" width="0.1524" layer="21"/>
<wire x1="-7.62" y1="-1.905" x2="-7.62" y2="0.635" width="0.1524" layer="21"/>
<wire x1="-7.62" y1="0.635" x2="-10.16" y2="0.635" width="0.1524" layer="21"/>
<wire x1="-10.16" y1="0.635" x2="-10.16" y2="-1.905" width="0.1524" layer="21"/>
<wire x1="-8.89" y1="6.985" x2="-8.89" y2="1.27" width="0.762" layer="21"/>
<wire x1="-7.62" y1="-1.905" x2="-5.08" y2="-1.905" width="0.1524" layer="21"/>
<wire x1="-5.08" y1="-1.905" x2="-5.08" y2="0.635" width="0.1524" layer="21"/>
<wire x1="-5.08" y1="0.635" x2="-7.62" y2="0.635" width="0.1524" layer="21"/>
<wire x1="-6.35" y1="6.985" x2="-6.35" y2="1.27" width="0.762" layer="21"/>
<wire x1="-5.08" y1="-1.905" x2="-2.54" y2="-1.905" width="0.1524" layer="21"/>
<wire x1="-2.54" y1="-1.905" x2="-2.54" y2="0.635" width="0.1524" layer="21"/>
<wire x1="-2.54" y1="0.635" x2="-5.08" y2="0.635" width="0.1524" layer="21"/>
<wire x1="-3.81" y1="6.985" x2="-3.81" y2="1.27" width="0.762" layer="21"/>
<wire x1="-2.54" y1="-1.905" x2="0" y2="-1.905" width="0.1524" layer="21"/>
<wire x1="0" y1="-1.905" x2="0" y2="0.635" width="0.1524" layer="21"/>
<wire x1="0" y1="0.635" x2="-2.54" y2="0.635" width="0.1524" layer="21"/>
<wire x1="-1.27" y1="6.985" x2="-1.27" y2="1.27" width="0.762" layer="21"/>
<wire x1="0" y1="-1.905" x2="2.54" y2="-1.905" width="0.1524" layer="21"/>
<wire x1="2.54" y1="-1.905" x2="2.54" y2="0.635" width="0.1524" layer="21"/>
<wire x1="2.54" y1="0.635" x2="0" y2="0.635" width="0.1524" layer="21"/>
<wire x1="1.27" y1="6.985" x2="1.27" y2="1.27" width="0.762" layer="21"/>
<wire x1="2.54" y1="-1.905" x2="5.08" y2="-1.905" width="0.1524" layer="21"/>
<wire x1="5.08" y1="-1.905" x2="5.08" y2="0.635" width="0.1524" layer="21"/>
<wire x1="5.08" y1="0.635" x2="2.54" y2="0.635" width="0.1524" layer="21"/>
<wire x1="3.81" y1="6.985" x2="3.81" y2="1.27" width="0.762" layer="21"/>
<wire x1="5.08" y1="-1.905" x2="7.62" y2="-1.905" width="0.1524" layer="21"/>
<wire x1="7.62" y1="-1.905" x2="7.62" y2="0.635" width="0.1524" layer="21"/>
<wire x1="7.62" y1="0.635" x2="5.08" y2="0.635" width="0.1524" layer="21"/>
<wire x1="6.35" y1="6.985" x2="6.35" y2="1.27" width="0.762" layer="21"/>
<wire x1="7.62" y1="-1.905" x2="10.16" y2="-1.905" width="0.1524" layer="21"/>
<wire x1="10.16" y1="-1.905" x2="10.16" y2="0.635" width="0.1524" layer="21"/>
<wire x1="10.16" y1="0.635" x2="7.62" y2="0.635" width="0.1524" layer="21"/>
<wire x1="8.89" y1="6.985" x2="8.89" y2="1.27" width="0.762" layer="21"/>
<pad name="2" x="-8.89" y="-3.81" drill="1.016" shape="octagon"/>
<pad name="4" x="-6.35" y="-3.81" drill="1.016" shape="octagon"/>
<pad name="6" x="-3.81" y="-3.81" drill="1.016" shape="octagon"/>
<pad name="8" x="-1.27" y="-3.81" drill="1.016" shape="octagon"/>
<pad name="10" x="1.27" y="-3.81" drill="1.016" shape="octagon"/>
<pad name="12" x="3.81" y="-3.81" drill="1.016" shape="octagon"/>
<pad name="14" x="6.35" y="-3.81" drill="1.016" shape="octagon"/>
<pad name="16" x="8.89" y="-3.81" drill="1.016" shape="octagon"/>
<pad name="1" x="-8.89" y="-6.35" drill="1.016" shape="octagon"/>
<pad name="3" x="-6.35" y="-6.35" drill="1.016" shape="octagon"/>
<pad name="5" x="-3.81" y="-6.35" drill="1.016" shape="octagon"/>
<pad name="7" x="-1.27" y="-6.35" drill="1.016" shape="octagon"/>
<pad name="9" x="1.27" y="-6.35" drill="1.016" shape="octagon"/>
<pad name="11" x="3.81" y="-6.35" drill="1.016" shape="octagon"/>
<pad name="13" x="6.35" y="-6.35" drill="1.016" shape="octagon"/>
<pad name="15" x="8.89" y="-6.35" drill="1.016" shape="octagon"/>
<text x="-10.795" y="-3.81" size="1.27" layer="25" ratio="10" rot="R90">&gt;NAME</text>
<text x="12.065" y="-3.81" size="1.27" layer="27" rot="R90">&gt;VALUE</text>
<rectangle x1="-9.271" y1="0.635" x2="-8.509" y2="1.143" layer="21"/>
<rectangle x1="-6.731" y1="0.635" x2="-5.969" y2="1.143" layer="21"/>
<rectangle x1="-4.191" y1="0.635" x2="-3.429" y2="1.143" layer="21"/>
<rectangle x1="-1.651" y1="0.635" x2="-0.889" y2="1.143" layer="21"/>
<rectangle x1="0.889" y1="0.635" x2="1.651" y2="1.143" layer="21"/>
<rectangle x1="3.429" y1="0.635" x2="4.191" y2="1.143" layer="21"/>
<rectangle x1="5.969" y1="0.635" x2="6.731" y2="1.143" layer="21"/>
<rectangle x1="8.509" y1="0.635" x2="9.271" y2="1.143" layer="21"/>
<rectangle x1="-9.271" y1="-2.921" x2="-8.509" y2="-1.905" layer="21"/>
<rectangle x1="-6.731" y1="-2.921" x2="-5.969" y2="-1.905" layer="21"/>
<rectangle x1="-9.271" y1="-5.461" x2="-8.509" y2="-4.699" layer="21"/>
<rectangle x1="-9.271" y1="-4.699" x2="-8.509" y2="-2.921" layer="51"/>
<rectangle x1="-6.731" y1="-4.699" x2="-5.969" y2="-2.921" layer="51"/>
<rectangle x1="-6.731" y1="-5.461" x2="-5.969" y2="-4.699" layer="21"/>
<rectangle x1="-4.191" y1="-2.921" x2="-3.429" y2="-1.905" layer="21"/>
<rectangle x1="-1.651" y1="-2.921" x2="-0.889" y2="-1.905" layer="21"/>
<rectangle x1="-4.191" y1="-5.461" x2="-3.429" y2="-4.699" layer="21"/>
<rectangle x1="-4.191" y1="-4.699" x2="-3.429" y2="-2.921" layer="51"/>
<rectangle x1="-1.651" y1="-4.699" x2="-0.889" y2="-2.921" layer="51"/>
<rectangle x1="-1.651" y1="-5.461" x2="-0.889" y2="-4.699" layer="21"/>
<rectangle x1="0.889" y1="-2.921" x2="1.651" y2="-1.905" layer="21"/>
<rectangle x1="3.429" y1="-2.921" x2="4.191" y2="-1.905" layer="21"/>
<rectangle x1="0.889" y1="-5.461" x2="1.651" y2="-4.699" layer="21"/>
<rectangle x1="0.889" y1="-4.699" x2="1.651" y2="-2.921" layer="51"/>
<rectangle x1="3.429" y1="-4.699" x2="4.191" y2="-2.921" layer="51"/>
<rectangle x1="3.429" y1="-5.461" x2="4.191" y2="-4.699" layer="21"/>
<rectangle x1="5.969" y1="-2.921" x2="6.731" y2="-1.905" layer="21"/>
<rectangle x1="8.509" y1="-2.921" x2="9.271" y2="-1.905" layer="21"/>
<rectangle x1="5.969" y1="-5.461" x2="6.731" y2="-4.699" layer="21"/>
<rectangle x1="5.969" y1="-4.699" x2="6.731" y2="-2.921" layer="51"/>
<rectangle x1="8.509" y1="-4.699" x2="9.271" y2="-2.921" layer="51"/>
<rectangle x1="8.509" y1="-5.461" x2="9.271" y2="-4.699" layer="21"/>
</package>
<package name="1X16">
<description>&lt;b&gt;PIN HEADER&lt;/b&gt;</description>
<wire x1="15.24" y1="0.635" x2="15.875" y2="1.27" width="0.1524" layer="21"/>
<wire x1="15.875" y1="1.27" x2="17.145" y2="1.27" width="0.1524" layer="21"/>
<wire x1="17.145" y1="1.27" x2="17.78" y2="0.635" width="0.1524" layer="21"/>
<wire x1="17.78" y1="0.635" x2="17.78" y2="-0.635" width="0.1524" layer="21"/>
<wire x1="17.78" y1="-0.635" x2="17.145" y2="-1.27" width="0.1524" layer="21"/>
<wire x1="17.145" y1="-1.27" x2="15.875" y2="-1.27" width="0.1524" layer="21"/>
<wire x1="15.875" y1="-1.27" x2="15.24" y2="-0.635" width="0.1524" layer="21"/>
<wire x1="10.795" y1="1.27" x2="12.065" y2="1.27" width="0.1524" layer="21"/>
<wire x1="12.065" y1="1.27" x2="12.7" y2="0.635" width="0.1524" layer="21"/>
<wire x1="12.7" y1="0.635" x2="12.7" y2="-0.635" width="0.1524" layer="21"/>
<wire x1="12.7" y1="-0.635" x2="12.065" y2="-1.27" width="0.1524" layer="21"/>
<wire x1="12.7" y1="0.635" x2="13.335" y2="1.27" width="0.1524" layer="21"/>
<wire x1="13.335" y1="1.27" x2="14.605" y2="1.27" width="0.1524" layer="21"/>
<wire x1="14.605" y1="1.27" x2="15.24" y2="0.635" width="0.1524" layer="21"/>
<wire x1="15.24" y1="0.635" x2="15.24" y2="-0.635" width="0.1524" layer="21"/>
<wire x1="15.24" y1="-0.635" x2="14.605" y2="-1.27" width="0.1524" layer="21"/>
<wire x1="14.605" y1="-1.27" x2="13.335" y2="-1.27" width="0.1524" layer="21"/>
<wire x1="13.335" y1="-1.27" x2="12.7" y2="-0.635" width="0.1524" layer="21"/>
<wire x1="7.62" y1="0.635" x2="8.255" y2="1.27" width="0.1524" layer="21"/>
<wire x1="8.255" y1="1.27" x2="9.525" y2="1.27" width="0.1524" layer="21"/>
<wire x1="9.525" y1="1.27" x2="10.16" y2="0.635" width="0.1524" layer="21"/>
<wire x1="10.16" y1="0.635" x2="10.16" y2="-0.635" width="0.1524" layer="21"/>
<wire x1="10.16" y1="-0.635" x2="9.525" y2="-1.27" width="0.1524" layer="21"/>
<wire x1="9.525" y1="-1.27" x2="8.255" y2="-1.27" width="0.1524" layer="21"/>
<wire x1="8.255" y1="-1.27" x2="7.62" y2="-0.635" width="0.1524" layer="21"/>
<wire x1="10.795" y1="1.27" x2="10.16" y2="0.635" width="0.1524" layer="21"/>
<wire x1="10.16" y1="-0.635" x2="10.795" y2="-1.27" width="0.1524" layer="21"/>
<wire x1="12.065" y1="-1.27" x2="10.795" y2="-1.27" width="0.1524" layer="21"/>
<wire x1="3.175" y1="1.27" x2="4.445" y2="1.27" width="0.1524" layer="21"/>
<wire x1="4.445" y1="1.27" x2="5.08" y2="0.635" width="0.1524" layer="21"/>
<wire x1="5.08" y1="0.635" x2="5.08" y2="-0.635" width="0.1524" layer="21"/>
<wire x1="5.08" y1="-0.635" x2="4.445" y2="-1.27" width="0.1524" layer="21"/>
<wire x1="5.08" y1="0.635" x2="5.715" y2="1.27" width="0.1524" layer="21"/>
<wire x1="5.715" y1="1.27" x2="6.985" y2="1.27" width="0.1524" layer="21"/>
<wire x1="6.985" y1="1.27" x2="7.62" y2="0.635" width="0.1524" layer="21"/>
<wire x1="7.62" y1="0.635" x2="7.62" y2="-0.635" width="0.1524" layer="21"/>
<wire x1="7.62" y1="-0.635" x2="6.985" y2="-1.27" width="0.1524" layer="21"/>
<wire x1="6.985" y1="-1.27" x2="5.715" y2="-1.27" width="0.1524" layer="21"/>
<wire x1="5.715" y1="-1.27" x2="5.08" y2="-0.635" width="0.1524" layer="21"/>
<wire x1="0" y1="0.635" x2="0.635" y2="1.27" width="0.1524" layer="21"/>
<wire x1="0.635" y1="1.27" x2="1.905" y2="1.27" width="0.1524" layer="21"/>
<wire x1="1.905" y1="1.27" x2="2.54" y2="0.635" width="0.1524" layer="21"/>
<wire x1="2.54" y1="0.635" x2="2.54" y2="-0.635" width="0.1524" layer="21"/>
<wire x1="2.54" y1="-0.635" x2="1.905" y2="-1.27" width="0.1524" layer="21"/>
<wire x1="1.905" y1="-1.27" x2="0.635" y2="-1.27" width="0.1524" layer="21"/>
<wire x1="0.635" y1="-1.27" x2="0" y2="-0.635" width="0.1524" layer="21"/>
<wire x1="3.175" y1="1.27" x2="2.54" y2="0.635" width="0.1524" layer="21"/>
<wire x1="2.54" y1="-0.635" x2="3.175" y2="-1.27" width="0.1524" layer="21"/>
<wire x1="4.445" y1="-1.27" x2="3.175" y2="-1.27" width="0.1524" layer="21"/>
<wire x1="-4.445" y1="1.27" x2="-3.175" y2="1.27" width="0.1524" layer="21"/>
<wire x1="-3.175" y1="1.27" x2="-2.54" y2="0.635" width="0.1524" layer="21"/>
<wire x1="-2.54" y1="0.635" x2="-2.54" y2="-0.635" width="0.1524" layer="21"/>
<wire x1="-2.54" y1="-0.635" x2="-3.175" y2="-1.27" width="0.1524" layer="21"/>
<wire x1="-2.54" y1="0.635" x2="-1.905" y2="1.27" width="0.1524" layer="21"/>
<wire x1="-1.905" y1="1.27" x2="-0.635" y2="1.27" width="0.1524" layer="21"/>
<wire x1="-0.635" y1="1.27" x2="0" y2="0.635" width="0.1524" layer="21"/>
<wire x1="0" y1="0.635" x2="0" y2="-0.635" width="0.1524" layer="21"/>
<wire x1="0" y1="-0.635" x2="-0.635" y2="-1.27" width="0.1524" layer="21"/>
<wire x1="-0.635" y1="-1.27" x2="-1.905" y2="-1.27" width="0.1524" layer="21"/>
<wire x1="-1.905" y1="-1.27" x2="-2.54" y2="-0.635" width="0.1524" layer="21"/>
<wire x1="-7.62" y1="0.635" x2="-6.985" y2="1.27" width="0.1524" layer="21"/>
<wire x1="-6.985" y1="1.27" x2="-5.715" y2="1.27" width="0.1524" layer="21"/>
<wire x1="-5.715" y1="1.27" x2="-5.08" y2="0.635" width="0.1524" layer="21"/>
<wire x1="-5.08" y1="0.635" x2="-5.08" y2="-0.635" width="0.1524" layer="21"/>
<wire x1="-5.08" y1="-0.635" x2="-5.715" y2="-1.27" width="0.1524" layer="21"/>
<wire x1="-5.715" y1="-1.27" x2="-6.985" y2="-1.27" width="0.1524" layer="21"/>
<wire x1="-6.985" y1="-1.27" x2="-7.62" y2="-0.635" width="0.1524" layer="21"/>
<wire x1="-4.445" y1="1.27" x2="-5.08" y2="0.635" width="0.1524" layer="21"/>
<wire x1="-5.08" y1="-0.635" x2="-4.445" y2="-1.27" width="0.1524" layer="21"/>
<wire x1="-3.175" y1="-1.27" x2="-4.445" y2="-1.27" width="0.1524" layer="21"/>
<wire x1="-12.065" y1="1.27" x2="-10.795" y2="1.27" width="0.1524" layer="21"/>
<wire x1="-10.795" y1="1.27" x2="-10.16" y2="0.635" width="0.1524" layer="21"/>
<wire x1="-10.16" y1="0.635" x2="-10.16" y2="-0.635" width="0.1524" layer="21"/>
<wire x1="-10.16" y1="-0.635" x2="-10.795" y2="-1.27" width="0.1524" layer="21"/>
<wire x1="-10.16" y1="0.635" x2="-9.525" y2="1.27" width="0.1524" layer="21"/>
<wire x1="-9.525" y1="1.27" x2="-8.255" y2="1.27" width="0.1524" layer="21"/>
<wire x1="-8.255" y1="1.27" x2="-7.62" y2="0.635" width="0.1524" layer="21"/>
<wire x1="-7.62" y1="0.635" x2="-7.62" y2="-0.635" width="0.1524" layer="21"/>
<wire x1="-7.62" y1="-0.635" x2="-8.255" y2="-1.27" width="0.1524" layer="21"/>
<wire x1="-8.255" y1="-1.27" x2="-9.525" y2="-1.27" width="0.1524" layer="21"/>
<wire x1="-9.525" y1="-1.27" x2="-10.16" y2="-0.635" width="0.1524" layer="21"/>
<wire x1="-15.24" y1="0.635" x2="-14.605" y2="1.27" width="0.1524" layer="21"/>
<wire x1="-14.605" y1="1.27" x2="-13.335" y2="1.27" width="0.1524" layer="21"/>
<wire x1="-13.335" y1="1.27" x2="-12.7" y2="0.635" width="0.1524" layer="21"/>
<wire x1="-12.7" y1="0.635" x2="-12.7" y2="-0.635" width="0.1524" layer="21"/>
<wire x1="-12.7" y1="-0.635" x2="-13.335" y2="-1.27" width="0.1524" layer="21"/>
<wire x1="-13.335" y1="-1.27" x2="-14.605" y2="-1.27" width="0.1524" layer="21"/>
<wire x1="-14.605" y1="-1.27" x2="-15.24" y2="-0.635" width="0.1524" layer="21"/>
<wire x1="-12.065" y1="1.27" x2="-12.7" y2="0.635" width="0.1524" layer="21"/>
<wire x1="-12.7" y1="-0.635" x2="-12.065" y2="-1.27" width="0.1524" layer="21"/>
<wire x1="-10.795" y1="-1.27" x2="-12.065" y2="-1.27" width="0.1524" layer="21"/>
<wire x1="-19.685" y1="1.27" x2="-18.415" y2="1.27" width="0.1524" layer="21"/>
<wire x1="-18.415" y1="1.27" x2="-17.78" y2="0.635" width="0.1524" layer="21"/>
<wire x1="-17.78" y1="0.635" x2="-17.78" y2="-0.635" width="0.1524" layer="21"/>
<wire x1="-17.78" y1="-0.635" x2="-18.415" y2="-1.27" width="0.1524" layer="21"/>
<wire x1="-17.78" y1="0.635" x2="-17.145" y2="1.27" width="0.1524" layer="21"/>
<wire x1="-17.145" y1="1.27" x2="-15.875" y2="1.27" width="0.1524" layer="21"/>
<wire x1="-15.875" y1="1.27" x2="-15.24" y2="0.635" width="0.1524" layer="21"/>
<wire x1="-15.24" y1="0.635" x2="-15.24" y2="-0.635" width="0.1524" layer="21"/>
<wire x1="-15.24" y1="-0.635" x2="-15.875" y2="-1.27" width="0.1524" layer="21"/>
<wire x1="-15.875" y1="-1.27" x2="-17.145" y2="-1.27" width="0.1524" layer="21"/>
<wire x1="-17.145" y1="-1.27" x2="-17.78" y2="-0.635" width="0.1524" layer="21"/>
<wire x1="-20.32" y1="0.635" x2="-20.32" y2="-0.635" width="0.1524" layer="21"/>
<wire x1="-19.685" y1="1.27" x2="-20.32" y2="0.635" width="0.1524" layer="21"/>
<wire x1="-20.32" y1="-0.635" x2="-19.685" y2="-1.27" width="0.1524" layer="21"/>
<wire x1="-18.415" y1="-1.27" x2="-19.685" y2="-1.27" width="0.1524" layer="21"/>
<wire x1="17.78" y1="0.635" x2="18.415" y2="1.27" width="0.1524" layer="21"/>
<wire x1="18.415" y1="1.27" x2="19.685" y2="1.27" width="0.1524" layer="21"/>
<wire x1="19.685" y1="1.27" x2="20.32" y2="0.635" width="0.1524" layer="21"/>
<wire x1="20.32" y1="0.635" x2="20.32" y2="-0.635" width="0.1524" layer="21"/>
<wire x1="20.32" y1="-0.635" x2="19.685" y2="-1.27" width="0.1524" layer="21"/>
<wire x1="19.685" y1="-1.27" x2="18.415" y2="-1.27" width="0.1524" layer="21"/>
<wire x1="18.415" y1="-1.27" x2="17.78" y2="-0.635" width="0.1524" layer="21"/>
<pad name="1" x="-19.05" y="0" drill="1.016" shape="long" rot="R90"/>
<pad name="2" x="-16.51" y="0" drill="1.016" shape="long" rot="R90"/>
<pad name="3" x="-13.97" y="0" drill="1.016" shape="long" rot="R90"/>
<pad name="4" x="-11.43" y="0" drill="1.016" shape="long" rot="R90"/>
<pad name="5" x="-8.89" y="0" drill="1.016" shape="long" rot="R90"/>
<pad name="6" x="-6.35" y="0" drill="1.016" shape="long" rot="R90"/>
<pad name="7" x="-3.81" y="0" drill="1.016" shape="long" rot="R90"/>
<pad name="8" x="-1.27" y="0" drill="1.016" shape="long" rot="R90"/>
<pad name="9" x="1.27" y="0" drill="1.016" shape="long" rot="R90"/>
<pad name="10" x="3.81" y="0" drill="1.016" shape="long" rot="R90"/>
<pad name="11" x="6.35" y="0" drill="1.016" shape="long" rot="R90"/>
<pad name="12" x="8.89" y="0" drill="1.016" shape="long" rot="R90"/>
<pad name="13" x="11.43" y="0" drill="1.016" shape="long" rot="R90"/>
<pad name="14" x="13.97" y="0" drill="1.016" shape="long" rot="R90"/>
<pad name="15" x="16.51" y="0" drill="1.016" shape="long" rot="R90"/>
<pad name="16" x="19.05" y="0" drill="1.016" shape="long" rot="R90"/>
<text x="-20.3962" y="1.8288" size="1.27" layer="25" ratio="10">&gt;NAME</text>
<text x="-20.32" y="-3.175" size="1.27" layer="27">&gt;VALUE</text>
<rectangle x1="16.256" y1="-0.254" x2="16.764" y2="0.254" layer="51"/>
<rectangle x1="13.716" y1="-0.254" x2="14.224" y2="0.254" layer="51"/>
<rectangle x1="11.176" y1="-0.254" x2="11.684" y2="0.254" layer="51"/>
<rectangle x1="8.636" y1="-0.254" x2="9.144" y2="0.254" layer="51"/>
<rectangle x1="6.096" y1="-0.254" x2="6.604" y2="0.254" layer="51"/>
<rectangle x1="3.556" y1="-0.254" x2="4.064" y2="0.254" layer="51"/>
<rectangle x1="1.016" y1="-0.254" x2="1.524" y2="0.254" layer="51"/>
<rectangle x1="-1.524" y1="-0.254" x2="-1.016" y2="0.254" layer="51"/>
<rectangle x1="-4.064" y1="-0.254" x2="-3.556" y2="0.254" layer="51"/>
<rectangle x1="-6.604" y1="-0.254" x2="-6.096" y2="0.254" layer="51"/>
<rectangle x1="-9.144" y1="-0.254" x2="-8.636" y2="0.254" layer="51"/>
<rectangle x1="-11.684" y1="-0.254" x2="-11.176" y2="0.254" layer="51"/>
<rectangle x1="-14.224" y1="-0.254" x2="-13.716" y2="0.254" layer="51"/>
<rectangle x1="-16.764" y1="-0.254" x2="-16.256" y2="0.254" layer="51"/>
<rectangle x1="-19.304" y1="-0.254" x2="-18.796" y2="0.254" layer="51"/>
<rectangle x1="18.796" y1="-0.254" x2="19.304" y2="0.254" layer="51"/>
</package>
<package name="1X16/90">
<description>&lt;b&gt;PIN HEADER&lt;/b&gt;</description>
<wire x1="-20.32" y1="-1.905" x2="-17.78" y2="-1.905" width="0.1524" layer="21"/>
<wire x1="-17.78" y1="-1.905" x2="-17.78" y2="0.635" width="0.1524" layer="21"/>
<wire x1="-17.78" y1="0.635" x2="-20.32" y2="0.635" width="0.1524" layer="21"/>
<wire x1="-20.32" y1="0.635" x2="-20.32" y2="-1.905" width="0.1524" layer="21"/>
<wire x1="-19.05" y1="6.985" x2="-19.05" y2="1.27" width="0.762" layer="21"/>
<wire x1="-17.78" y1="-1.905" x2="-15.24" y2="-1.905" width="0.1524" layer="21"/>
<wire x1="-15.24" y1="-1.905" x2="-15.24" y2="0.635" width="0.1524" layer="21"/>
<wire x1="-15.24" y1="0.635" x2="-17.78" y2="0.635" width="0.1524" layer="21"/>
<wire x1="-16.51" y1="6.985" x2="-16.51" y2="1.27" width="0.762" layer="21"/>
<wire x1="-15.24" y1="-1.905" x2="-12.7" y2="-1.905" width="0.1524" layer="21"/>
<wire x1="-12.7" y1="-1.905" x2="-12.7" y2="0.635" width="0.1524" layer="21"/>
<wire x1="-12.7" y1="0.635" x2="-15.24" y2="0.635" width="0.1524" layer="21"/>
<wire x1="-13.97" y1="6.985" x2="-13.97" y2="1.27" width="0.762" layer="21"/>
<wire x1="-12.7" y1="-1.905" x2="-10.16" y2="-1.905" width="0.1524" layer="21"/>
<wire x1="-10.16" y1="-1.905" x2="-10.16" y2="0.635" width="0.1524" layer="21"/>
<wire x1="-10.16" y1="0.635" x2="-12.7" y2="0.635" width="0.1524" layer="21"/>
<wire x1="-11.43" y1="6.985" x2="-11.43" y2="1.27" width="0.762" layer="21"/>
<wire x1="-10.16" y1="-1.905" x2="-7.62" y2="-1.905" width="0.1524" layer="21"/>
<wire x1="-7.62" y1="-1.905" x2="-7.62" y2="0.635" width="0.1524" layer="21"/>
<wire x1="-7.62" y1="0.635" x2="-10.16" y2="0.635" width="0.1524" layer="21"/>
<wire x1="-8.89" y1="6.985" x2="-8.89" y2="1.27" width="0.762" layer="21"/>
<wire x1="-7.62" y1="-1.905" x2="-5.08" y2="-1.905" width="0.1524" layer="21"/>
<wire x1="-5.08" y1="-1.905" x2="-5.08" y2="0.635" width="0.1524" layer="21"/>
<wire x1="-5.08" y1="0.635" x2="-7.62" y2="0.635" width="0.1524" layer="21"/>
<wire x1="-6.35" y1="6.985" x2="-6.35" y2="1.27" width="0.762" layer="21"/>
<wire x1="-5.08" y1="-1.905" x2="-2.54" y2="-1.905" width="0.1524" layer="21"/>
<wire x1="-2.54" y1="-1.905" x2="-2.54" y2="0.635" width="0.1524" layer="21"/>
<wire x1="-2.54" y1="0.635" x2="-5.08" y2="0.635" width="0.1524" layer="21"/>
<wire x1="-3.81" y1="6.985" x2="-3.81" y2="1.27" width="0.762" layer="21"/>
<wire x1="-2.54" y1="-1.905" x2="0" y2="-1.905" width="0.1524" layer="21"/>
<wire x1="0" y1="-1.905" x2="0" y2="0.635" width="0.1524" layer="21"/>
<wire x1="0" y1="0.635" x2="-2.54" y2="0.635" width="0.1524" layer="21"/>
<wire x1="-1.27" y1="6.985" x2="-1.27" y2="1.27" width="0.762" layer="21"/>
<wire x1="0" y1="-1.905" x2="2.54" y2="-1.905" width="0.1524" layer="21"/>
<wire x1="2.54" y1="-1.905" x2="2.54" y2="0.635" width="0.1524" layer="21"/>
<wire x1="2.54" y1="0.635" x2="0" y2="0.635" width="0.1524" layer="21"/>
<wire x1="1.27" y1="6.985" x2="1.27" y2="1.27" width="0.762" layer="21"/>
<wire x1="2.54" y1="-1.905" x2="5.08" y2="-1.905" width="0.1524" layer="21"/>
<wire x1="5.08" y1="-1.905" x2="5.08" y2="0.635" width="0.1524" layer="21"/>
<wire x1="5.08" y1="0.635" x2="2.54" y2="0.635" width="0.1524" layer="21"/>
<wire x1="3.81" y1="6.985" x2="3.81" y2="1.27" width="0.762" layer="21"/>
<wire x1="5.08" y1="-1.905" x2="7.62" y2="-1.905" width="0.1524" layer="21"/>
<wire x1="7.62" y1="-1.905" x2="7.62" y2="0.635" width="0.1524" layer="21"/>
<wire x1="7.62" y1="0.635" x2="5.08" y2="0.635" width="0.1524" layer="21"/>
<wire x1="6.35" y1="6.985" x2="6.35" y2="1.27" width="0.762" layer="21"/>
<wire x1="7.62" y1="-1.905" x2="10.16" y2="-1.905" width="0.1524" layer="21"/>
<wire x1="10.16" y1="-1.905" x2="10.16" y2="0.635" width="0.1524" layer="21"/>
<wire x1="10.16" y1="0.635" x2="7.62" y2="0.635" width="0.1524" layer="21"/>
<wire x1="8.89" y1="6.985" x2="8.89" y2="1.27" width="0.762" layer="21"/>
<wire x1="10.16" y1="-1.905" x2="12.7" y2="-1.905" width="0.1524" layer="21"/>
<wire x1="12.7" y1="-1.905" x2="12.7" y2="0.635" width="0.1524" layer="21"/>
<wire x1="12.7" y1="0.635" x2="10.16" y2="0.635" width="0.1524" layer="21"/>
<wire x1="11.43" y1="6.985" x2="11.43" y2="1.27" width="0.762" layer="21"/>
<wire x1="12.7" y1="-1.905" x2="15.24" y2="-1.905" width="0.1524" layer="21"/>
<wire x1="15.24" y1="-1.905" x2="15.24" y2="0.635" width="0.1524" layer="21"/>
<wire x1="15.24" y1="0.635" x2="12.7" y2="0.635" width="0.1524" layer="21"/>
<wire x1="13.97" y1="6.985" x2="13.97" y2="1.27" width="0.762" layer="21"/>
<wire x1="15.24" y1="-1.905" x2="17.78" y2="-1.905" width="0.1524" layer="21"/>
<wire x1="17.78" y1="-1.905" x2="17.78" y2="0.635" width="0.1524" layer="21"/>
<wire x1="17.78" y1="0.635" x2="15.24" y2="0.635" width="0.1524" layer="21"/>
<wire x1="16.51" y1="6.985" x2="16.51" y2="1.27" width="0.762" layer="21"/>
<wire x1="17.78" y1="-1.905" x2="20.32" y2="-1.905" width="0.1524" layer="21"/>
<wire x1="20.32" y1="-1.905" x2="20.32" y2="0.635" width="0.1524" layer="21"/>
<wire x1="20.32" y1="0.635" x2="17.78" y2="0.635" width="0.1524" layer="21"/>
<wire x1="19.05" y1="6.985" x2="19.05" y2="1.27" width="0.762" layer="21"/>
<pad name="1" x="-19.05" y="-3.81" drill="1.016" shape="long" rot="R90"/>
<pad name="2" x="-16.51" y="-3.81" drill="1.016" shape="long" rot="R90"/>
<pad name="3" x="-13.97" y="-3.81" drill="1.016" shape="long" rot="R90"/>
<pad name="4" x="-11.43" y="-3.81" drill="1.016" shape="long" rot="R90"/>
<pad name="5" x="-8.89" y="-3.81" drill="1.016" shape="long" rot="R90"/>
<pad name="6" x="-6.35" y="-3.81" drill="1.016" shape="long" rot="R90"/>
<pad name="7" x="-3.81" y="-3.81" drill="1.016" shape="long" rot="R90"/>
<pad name="8" x="-1.27" y="-3.81" drill="1.016" shape="long" rot="R90"/>
<pad name="9" x="1.27" y="-3.81" drill="1.016" shape="long" rot="R90"/>
<pad name="10" x="3.81" y="-3.81" drill="1.016" shape="long" rot="R90"/>
<pad name="11" x="6.35" y="-3.81" drill="1.016" shape="long" rot="R90"/>
<pad name="12" x="8.89" y="-3.81" drill="1.016" shape="long" rot="R90"/>
<pad name="13" x="11.43" y="-3.81" drill="1.016" shape="long" rot="R90"/>
<pad name="14" x="13.97" y="-3.81" drill="1.016" shape="long" rot="R90"/>
<pad name="15" x="16.51" y="-3.81" drill="1.016" shape="long" rot="R90"/>
<pad name="16" x="19.05" y="-3.81" drill="1.016" shape="long" rot="R90"/>
<text x="-20.955" y="-3.81" size="1.27" layer="25" ratio="10" rot="R90">&gt;NAME</text>
<text x="22.225" y="-3.81" size="1.27" layer="27" rot="R90">&gt;VALUE</text>
<rectangle x1="-19.431" y1="0.635" x2="-18.669" y2="1.143" layer="21"/>
<rectangle x1="-16.891" y1="0.635" x2="-16.129" y2="1.143" layer="21"/>
<rectangle x1="-14.351" y1="0.635" x2="-13.589" y2="1.143" layer="21"/>
<rectangle x1="-11.811" y1="0.635" x2="-11.049" y2="1.143" layer="21"/>
<rectangle x1="-9.271" y1="0.635" x2="-8.509" y2="1.143" layer="21"/>
<rectangle x1="-6.731" y1="0.635" x2="-5.969" y2="1.143" layer="21"/>
<rectangle x1="-4.191" y1="0.635" x2="-3.429" y2="1.143" layer="21"/>
<rectangle x1="-1.651" y1="0.635" x2="-0.889" y2="1.143" layer="21"/>
<rectangle x1="0.889" y1="0.635" x2="1.651" y2="1.143" layer="21"/>
<rectangle x1="3.429" y1="0.635" x2="4.191" y2="1.143" layer="21"/>
<rectangle x1="5.969" y1="0.635" x2="6.731" y2="1.143" layer="21"/>
<rectangle x1="8.509" y1="0.635" x2="9.271" y2="1.143" layer="21"/>
<rectangle x1="11.049" y1="0.635" x2="11.811" y2="1.143" layer="21"/>
<rectangle x1="13.589" y1="0.635" x2="14.351" y2="1.143" layer="21"/>
<rectangle x1="16.129" y1="0.635" x2="16.891" y2="1.143" layer="21"/>
<rectangle x1="18.669" y1="0.635" x2="19.431" y2="1.143" layer="21"/>
<rectangle x1="-19.431" y1="-2.921" x2="-18.669" y2="-1.905" layer="21"/>
<rectangle x1="-16.891" y1="-2.921" x2="-16.129" y2="-1.905" layer="21"/>
<rectangle x1="-14.351" y1="-2.921" x2="-13.589" y2="-1.905" layer="21"/>
<rectangle x1="-11.811" y1="-2.921" x2="-11.049" y2="-1.905" layer="21"/>
<rectangle x1="-9.271" y1="-2.921" x2="-8.509" y2="-1.905" layer="21"/>
<rectangle x1="-6.731" y1="-2.921" x2="-5.969" y2="-1.905" layer="21"/>
<rectangle x1="-4.191" y1="-2.921" x2="-3.429" y2="-1.905" layer="21"/>
<rectangle x1="-1.651" y1="-2.921" x2="-0.889" y2="-1.905" layer="21"/>
<rectangle x1="0.889" y1="-2.921" x2="1.651" y2="-1.905" layer="21"/>
<rectangle x1="3.429" y1="-2.921" x2="4.191" y2="-1.905" layer="21"/>
<rectangle x1="5.969" y1="-2.921" x2="6.731" y2="-1.905" layer="21"/>
<rectangle x1="8.509" y1="-2.921" x2="9.271" y2="-1.905" layer="21"/>
<rectangle x1="11.049" y1="-2.921" x2="11.811" y2="-1.905" layer="21"/>
<rectangle x1="13.589" y1="-2.921" x2="14.351" y2="-1.905" layer="21"/>
<rectangle x1="16.129" y1="-2.921" x2="16.891" y2="-1.905" layer="21"/>
<rectangle x1="18.669" y1="-2.921" x2="19.431" y2="-1.905" layer="21"/>
</package>
</packages>
<symbols>
<symbol name="PINH2X8">
<wire x1="-6.35" y1="-12.7" x2="8.89" y2="-12.7" width="0.4064" layer="94"/>
<wire x1="8.89" y1="-12.7" x2="8.89" y2="10.16" width="0.4064" layer="94"/>
<wire x1="8.89" y1="10.16" x2="-6.35" y2="10.16" width="0.4064" layer="94"/>
<wire x1="-6.35" y1="10.16" x2="-6.35" y2="-12.7" width="0.4064" layer="94"/>
<text x="-6.35" y="10.795" size="1.778" layer="95">&gt;NAME</text>
<text x="-6.35" y="-15.24" size="1.778" layer="96">&gt;VALUE</text>
<pin name="1" x="-2.54" y="7.62" visible="pad" length="short" direction="pas" function="dot"/>
<pin name="2" x="5.08" y="7.62" visible="pad" length="short" direction="pas" function="dot" rot="R180"/>
<pin name="3" x="-2.54" y="5.08" visible="pad" length="short" direction="pas" function="dot"/>
<pin name="4" x="5.08" y="5.08" visible="pad" length="short" direction="pas" function="dot" rot="R180"/>
<pin name="5" x="-2.54" y="2.54" visible="pad" length="short" direction="pas" function="dot"/>
<pin name="6" x="5.08" y="2.54" visible="pad" length="short" direction="pas" function="dot" rot="R180"/>
<pin name="7" x="-2.54" y="0" visible="pad" length="short" direction="pas" function="dot"/>
<pin name="8" x="5.08" y="0" visible="pad" length="short" direction="pas" function="dot" rot="R180"/>
<pin name="9" x="-2.54" y="-2.54" visible="pad" length="short" direction="pas" function="dot"/>
<pin name="10" x="5.08" y="-2.54" visible="pad" length="short" direction="pas" function="dot" rot="R180"/>
<pin name="11" x="-2.54" y="-5.08" visible="pad" length="short" direction="pas" function="dot"/>
<pin name="12" x="5.08" y="-5.08" visible="pad" length="short" direction="pas" function="dot" rot="R180"/>
<pin name="13" x="-2.54" y="-7.62" visible="pad" length="short" direction="pas" function="dot"/>
<pin name="14" x="5.08" y="-7.62" visible="pad" length="short" direction="pas" function="dot" rot="R180"/>
<pin name="15" x="-2.54" y="-10.16" visible="pad" length="short" direction="pas" function="dot"/>
<pin name="16" x="5.08" y="-10.16" visible="pad" length="short" direction="pas" function="dot" rot="R180"/>
</symbol>
<symbol name="PINHD16">
<wire x1="-6.35" y1="-22.86" x2="1.27" y2="-22.86" width="0.4064" layer="94"/>
<wire x1="1.27" y1="-22.86" x2="1.27" y2="20.32" width="0.4064" layer="94"/>
<wire x1="1.27" y1="20.32" x2="-6.35" y2="20.32" width="0.4064" layer="94"/>
<wire x1="-6.35" y1="20.32" x2="-6.35" y2="-22.86" width="0.4064" layer="94"/>
<text x="-6.35" y="20.955" size="1.778" layer="95">&gt;NAME</text>
<text x="-6.35" y="-25.4" size="1.778" layer="96">&gt;VALUE</text>
<pin name="1" x="-2.54" y="17.78" visible="pad" length="short" direction="pas" function="dot"/>
<pin name="2" x="-2.54" y="15.24" visible="pad" length="short" direction="pas" function="dot"/>
<pin name="3" x="-2.54" y="12.7" visible="pad" length="short" direction="pas" function="dot"/>
<pin name="4" x="-2.54" y="10.16" visible="pad" length="short" direction="pas" function="dot"/>
<pin name="5" x="-2.54" y="7.62" visible="pad" length="short" direction="pas" function="dot"/>
<pin name="6" x="-2.54" y="5.08" visible="pad" length="short" direction="pas" function="dot"/>
<pin name="7" x="-2.54" y="2.54" visible="pad" length="short" direction="pas" function="dot"/>
<pin name="8" x="-2.54" y="0" visible="pad" length="short" direction="pas" function="dot"/>
<pin name="9" x="-2.54" y="-2.54" visible="pad" length="short" direction="pas" function="dot"/>
<pin name="10" x="-2.54" y="-5.08" visible="pad" length="short" direction="pas" function="dot"/>
<pin name="11" x="-2.54" y="-7.62" visible="pad" length="short" direction="pas" function="dot"/>
<pin name="12" x="-2.54" y="-10.16" visible="pad" length="short" direction="pas" function="dot"/>
<pin name="13" x="-2.54" y="-12.7" visible="pad" length="short" direction="pas" function="dot"/>
<pin name="14" x="-2.54" y="-15.24" visible="pad" length="short" direction="pas" function="dot"/>
<pin name="15" x="-2.54" y="-17.78" visible="pad" length="short" direction="pas" function="dot"/>
<pin name="16" x="-2.54" y="-20.32" visible="pad" length="short" direction="pas" function="dot"/>
</symbol>
</symbols>
<devicesets>
<deviceset name="PINHD-2X8" prefix="JP" uservalue="yes">
<description>&lt;b&gt;PIN HEADER&lt;/b&gt;</description>
<gates>
<gate name="A" symbol="PINH2X8" x="0" y="0"/>
</gates>
<devices>
<device name="" package="2X08">
<connects>
<connect gate="A" pin="1" pad="1"/>
<connect gate="A" pin="10" pad="10"/>
<connect gate="A" pin="11" pad="11"/>
<connect gate="A" pin="12" pad="12"/>
<connect gate="A" pin="13" pad="13"/>
<connect gate="A" pin="14" pad="14"/>
<connect gate="A" pin="15" pad="15"/>
<connect gate="A" pin="16" pad="16"/>
<connect gate="A" pin="2" pad="2"/>
<connect gate="A" pin="3" pad="3"/>
<connect gate="A" pin="4" pad="4"/>
<connect gate="A" pin="5" pad="5"/>
<connect gate="A" pin="6" pad="6"/>
<connect gate="A" pin="7" pad="7"/>
<connect gate="A" pin="8" pad="8"/>
<connect gate="A" pin="9" pad="9"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="/90" package="2X08/90">
<connects>
<connect gate="A" pin="1" pad="1"/>
<connect gate="A" pin="10" pad="10"/>
<connect gate="A" pin="11" pad="11"/>
<connect gate="A" pin="12" pad="12"/>
<connect gate="A" pin="13" pad="13"/>
<connect gate="A" pin="14" pad="14"/>
<connect gate="A" pin="15" pad="15"/>
<connect gate="A" pin="16" pad="16"/>
<connect gate="A" pin="2" pad="2"/>
<connect gate="A" pin="3" pad="3"/>
<connect gate="A" pin="4" pad="4"/>
<connect gate="A" pin="5" pad="5"/>
<connect gate="A" pin="6" pad="6"/>
<connect gate="A" pin="7" pad="7"/>
<connect gate="A" pin="8" pad="8"/>
<connect gate="A" pin="9" pad="9"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
<deviceset name="PINHD-1X16" prefix="JP" uservalue="yes">
<description>&lt;b&gt;PIN HEADER&lt;/b&gt;</description>
<gates>
<gate name="A" symbol="PINHD16" x="0" y="0"/>
</gates>
<devices>
<device name="" package="1X16">
<connects>
<connect gate="A" pin="1" pad="1"/>
<connect gate="A" pin="10" pad="10"/>
<connect gate="A" pin="11" pad="11"/>
<connect gate="A" pin="12" pad="12"/>
<connect gate="A" pin="13" pad="13"/>
<connect gate="A" pin="14" pad="14"/>
<connect gate="A" pin="15" pad="15"/>
<connect gate="A" pin="16" pad="16"/>
<connect gate="A" pin="2" pad="2"/>
<connect gate="A" pin="3" pad="3"/>
<connect gate="A" pin="4" pad="4"/>
<connect gate="A" pin="5" pad="5"/>
<connect gate="A" pin="6" pad="6"/>
<connect gate="A" pin="7" pad="7"/>
<connect gate="A" pin="8" pad="8"/>
<connect gate="A" pin="9" pad="9"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="/90" package="1X16/90">
<connects>
<connect gate="A" pin="1" pad="1"/>
<connect gate="A" pin="10" pad="10"/>
<connect gate="A" pin="11" pad="11"/>
<connect gate="A" pin="12" pad="12"/>
<connect gate="A" pin="13" pad="13"/>
<connect gate="A" pin="14" pad="14"/>
<connect gate="A" pin="15" pad="15"/>
<connect gate="A" pin="16" pad="16"/>
<connect gate="A" pin="2" pad="2"/>
<connect gate="A" pin="3" pad="3"/>
<connect gate="A" pin="4" pad="4"/>
<connect gate="A" pin="5" pad="5"/>
<connect gate="A" pin="6" pad="6"/>
<connect gate="A" pin="7" pad="7"/>
<connect gate="A" pin="8" pad="8"/>
<connect gate="A" pin="9" pad="9"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
</devicesets>
</library>
</libraries>
<attributes>
</attributes>
<variantdefs>
</variantdefs>
<classes>
<class number="0" name="default" width="0" drill="0">
</class>
</classes>
<parts>
<part name="LCD1" library="display-lcd" deviceset="TUXGR_20X2" device="" value="24x2 LCD Display"/>
<part name="H1" library="pinhead" deviceset="PINHD-2X8" device="" value="1"/>
<part name="P1" library="wirepad" deviceset="1,6/0,9" device="" value=" "/>
<part name="P2" library="wirepad" deviceset="1,6/0,9" device="" value=" "/>
<part name="P3" library="wirepad" deviceset="1,6/0,9" device="" value=" "/>
<part name="P4" library="wirepad" deviceset="1,6/0,9" device="" value=" "/>
<part name="P5" library="wirepad" deviceset="1,6/0,9" device="" value=" "/>
<part name="P6" library="wirepad" deviceset="1,6/0,9" device="" value=" "/>
<part name="P7" library="wirepad" deviceset="1,6/0,9" device="" value=" "/>
<part name="P8" library="wirepad" deviceset="1,6/0,9" device="" value=" "/>
<part name="P9" library="wirepad" deviceset="1,6/0,9" device="" value=" "/>
<part name="P10" library="wirepad" deviceset="1,6/0,9" device="" value=" "/>
<part name="P11" library="wirepad" deviceset="1,6/0,9" device="" value=" "/>
<part name="P12" library="wirepad" deviceset="1,6/0,9" device="" value=" "/>
<part name="P13" library="wirepad" deviceset="1,6/0,9" device="" value=" "/>
<part name="P14" library="wirepad" deviceset="1,6/0,9" device="" value=" "/>
<part name="P15" library="wirepad" deviceset="1,6/0,9" device="" value=" "/>
<part name="P16" library="wirepad" deviceset="1,6/0,9" device="" value=" "/>
<part name="H2" library="pinhead" deviceset="PINHD-1X16" device="" value="1"/>
<part name="1X9_P1" library="wirepad" deviceset="1,6/0,9" device="" value=" "/>
<part name="1X9_P2" library="wirepad" deviceset="1,6/0,9" device="" value=" "/>
<part name="1X9_P3" library="wirepad" deviceset="1,6/0,9" device="" value=" "/>
<part name="1X9_P4" library="wirepad" deviceset="1,6/0,9" device="" value=" "/>
<part name="1X9_P5" library="wirepad" deviceset="1,6/0,9" device="" value=" "/>
<part name="1X9_P6" library="wirepad" deviceset="1,6/0,9" device="" value=" "/>
<part name="1X9_P7" library="wirepad" deviceset="1,6/0,9" device="" value=" "/>
<part name="1X9_P8" library="wirepad" deviceset="1,6/0,9" device="" value=" "/>
<part name="1X9_P9" library="wirepad" deviceset="1,6/0,9" device="" value=" "/>
<part name="1X9_P10" library="wirepad" deviceset="1,6/0,9" device="" value=" "/>
<part name="1X9_P11" library="wirepad" deviceset="1,6/0,9" device="" value=" "/>
<part name="1X9_P12" library="wirepad" deviceset="1,6/0,9" device="" value=" "/>
<part name="1X9_P13" library="wirepad" deviceset="1,6/0,9" device="" value=" "/>
<part name="1X9_P14" library="wirepad" deviceset="1,6/0,9" device="" value=" "/>
<part name="1X9_P15" library="wirepad" deviceset="1,6/0,9" device="" value=" "/>
<part name="1X9_P16" library="wirepad" deviceset="1,6/0,9" device="" value=" "/>
</parts>
<sheets>
<sheet>
<plain>
<text x="-48.26" y="99.06" size="1.778" layer="97">*note: The LCD display in the parts
list has a backlight, and thus pins
15 &amp; 16 are not NC, instead
15 = +5V, 16 = GND ( for backlight )</text>
<wire x1="-10.16" y1="93.98" x2="134.62" y2="93.98" width="0.1524" layer="97" style="shortdash"/>
<wire x1="134.62" y1="93.98" x2="134.62" y2="-7.62" width="0.1524" layer="97" style="shortdash"/>
<wire x1="134.62" y1="-7.62" x2="-10.16" y2="-7.62" width="0.1524" layer="97" style="shortdash"/>
<wire x1="-10.16" y1="-7.62" x2="-10.16" y2="93.98" width="0.1524" layer="97" style="shortdash"/>
<text x="-7.62" y="-3.81" size="1.778" layer="97">There Is A 2x8 Female Header Soldered To The LCD solder pads. You then make a 2x8_to_1x16 board and that connects via a 2x8
male header to the LCD's female header. P1-P16 on the 2x8_to_1x16 board have a 16 conductor ribbon cable soldered on.</text>
<text x="99.06" y="88.9" size="2.54" layer="97">2x8_to_1x16 Board</text>
<wire x1="137.16" y1="93.98" x2="137.16" y2="-7.62" width="0.1524" layer="97" style="shortdash"/>
<wire x1="137.16" y1="-7.62" x2="177.8" y2="-7.62" width="0.1524" layer="97" style="shortdash"/>
<wire x1="177.8" y1="-7.62" x2="177.8" y2="93.98" width="0.1524" layer="97" style="shortdash"/>
<wire x1="177.8" y1="93.98" x2="137.16" y2="93.98" width="0.1524" layer="97" style="shortdash"/>
<text x="144.78" y="83.82" size="2.54" layer="97">16 Conductor
Ribbon Cable</text>
<wire x1="180.34" y1="93.98" x2="180.34" y2="-7.62" width="0.1524" layer="97" style="shortdash"/>
<wire x1="180.34" y1="-7.62" x2="218.44" y2="-7.62" width="0.1524" layer="97" style="shortdash"/>
<wire x1="218.44" y1="-7.62" x2="218.44" y2="93.98" width="0.1524" layer="97" style="shortdash"/>
<wire x1="218.44" y1="93.98" x2="180.34" y2="93.98" width="0.1524" layer="97" style="shortdash"/>
<text x="185.42" y="88.9" size="2.54" layer="97">1x9_to_1x9 Board</text>
<text x="182.88" y="78.74" size="1.6764" layer="97">Ribbon cable soldered directly
on board. H2 has male pin
header to connect to Controller.</text>
</plain>
<instances>
<instance part="LCD1" gate="G$1" x="20.32" y="99.06"/>
<instance part="H1" gate="A" x="83.82" y="45.72"/>
<instance part="P1" gate="1" x="106.68" y="63.5" smashed="yes" rot="R180">
<attribute name="NAME" x="111.379" y="64.4398" size="1.778" layer="95" rot="R180"/>
<attribute name="VALUE" x="107.823" y="66.802" size="1.778" layer="96" rot="R180"/>
</instance>
<instance part="P2" gate="1" x="106.68" y="60.96" smashed="yes" rot="R180">
<attribute name="NAME" x="111.379" y="61.6458" size="1.778" layer="95" rot="R180"/>
<attribute name="VALUE" x="107.823" y="64.262" size="1.778" layer="96" rot="R180"/>
</instance>
<instance part="P3" gate="1" x="106.68" y="58.42" smashed="yes">
<attribute name="NAME" x="101.727" y="57.7342" size="1.778" layer="95"/>
<attribute name="VALUE" x="105.537" y="55.118" size="1.778" layer="96"/>
</instance>
<instance part="P4" gate="1" x="106.68" y="55.88" smashed="yes" rot="R180">
<attribute name="NAME" x="111.379" y="56.5658" size="1.778" layer="95" rot="R180"/>
<attribute name="VALUE" x="107.823" y="59.182" size="1.778" layer="96" rot="R180"/>
</instance>
<instance part="P5" gate="1" x="106.68" y="53.34" smashed="yes">
<attribute name="NAME" x="101.981" y="52.4002" size="1.778" layer="95"/>
<attribute name="VALUE" x="105.537" y="50.038" size="1.778" layer="96"/>
</instance>
<instance part="P6" gate="1" x="106.68" y="50.8" smashed="yes" rot="R180">
<attribute name="NAME" x="111.379" y="51.7398" size="1.778" layer="95" rot="R180"/>
<attribute name="VALUE" x="107.823" y="54.102" size="1.778" layer="96" rot="R180"/>
</instance>
<instance part="P7" gate="1" x="106.68" y="48.26" smashed="yes">
<attribute name="NAME" x="102.235" y="47.3202" size="1.778" layer="95"/>
<attribute name="VALUE" x="105.537" y="44.958" size="1.778" layer="96"/>
</instance>
<instance part="P8" gate="1" x="106.68" y="45.72" smashed="yes" rot="R180">
<attribute name="NAME" x="111.379" y="46.6598" size="1.778" layer="95" rot="R180"/>
<attribute name="VALUE" x="107.823" y="49.022" size="1.778" layer="96" rot="R180"/>
</instance>
<instance part="P9" gate="1" x="106.68" y="43.18" smashed="yes">
<attribute name="NAME" x="102.235" y="42.2402" size="1.778" layer="95"/>
<attribute name="VALUE" x="105.537" y="39.878" size="1.778" layer="96"/>
</instance>
<instance part="P10" gate="1" x="106.68" y="40.64" smashed="yes" rot="R180">
<attribute name="NAME" x="112.649" y="41.3258" size="1.778" layer="95" rot="R180"/>
<attribute name="VALUE" x="107.823" y="43.942" size="1.778" layer="96" rot="R180"/>
</instance>
<instance part="P11" gate="1" x="106.68" y="38.1" smashed="yes">
<attribute name="NAME" x="101.473" y="37.1602" size="1.778" layer="95"/>
<attribute name="VALUE" x="105.537" y="34.798" size="1.778" layer="96"/>
</instance>
<instance part="P12" gate="1" x="106.68" y="35.56" smashed="yes" rot="R180">
<attribute name="NAME" x="112.649" y="36.4998" size="1.778" layer="95" rot="R180"/>
<attribute name="VALUE" x="107.823" y="38.862" size="1.778" layer="96" rot="R180"/>
</instance>
<instance part="P13" gate="1" x="106.68" y="33.02" smashed="yes">
<attribute name="NAME" x="100.965" y="32.0802" size="1.778" layer="95"/>
<attribute name="VALUE" x="105.537" y="29.718" size="1.778" layer="96"/>
</instance>
<instance part="P14" gate="1" x="106.68" y="30.48" smashed="yes" rot="R180">
<attribute name="NAME" x="112.649" y="31.1658" size="1.778" layer="95" rot="R180"/>
<attribute name="VALUE" x="107.823" y="33.782" size="1.778" layer="96" rot="R180"/>
</instance>
<instance part="P15" gate="1" x="106.68" y="27.94" smashed="yes" rot="R180">
<attribute name="NAME" x="112.649" y="28.6258" size="1.778" layer="95" rot="R180"/>
<attribute name="VALUE" x="107.823" y="31.242" size="1.778" layer="96" rot="R180"/>
</instance>
<instance part="P16" gate="1" x="106.68" y="25.4" smashed="yes" rot="R180">
<attribute name="NAME" x="112.649" y="26.3398" size="1.778" layer="95" rot="R180"/>
<attribute name="VALUE" x="107.823" y="28.702" size="1.778" layer="96" rot="R180"/>
</instance>
<instance part="H2" gate="A" x="213.36" y="45.72"/>
<instance part="1X9_P1" gate="1" x="187.96" y="63.5" smashed="yes">
<attribute name="NAME" x="184.277" y="62.8142" size="1.778" layer="95"/>
<attribute name="VALUE" x="186.817" y="60.198" size="1.778" layer="96"/>
</instance>
<instance part="1X9_P2" gate="1" x="187.96" y="60.96" smashed="yes">
<attribute name="NAME" x="184.277" y="60.2742" size="1.778" layer="95"/>
<attribute name="VALUE" x="186.817" y="57.658" size="1.778" layer="96"/>
</instance>
<instance part="1X9_P3" gate="1" x="187.96" y="58.42" smashed="yes">
<attribute name="NAME" x="184.277" y="57.7342" size="1.778" layer="95"/>
<attribute name="VALUE" x="186.817" y="55.118" size="1.778" layer="96"/>
</instance>
<instance part="1X9_P4" gate="1" x="187.96" y="55.88" smashed="yes">
<attribute name="NAME" x="184.277" y="55.1942" size="1.778" layer="95"/>
<attribute name="VALUE" x="186.817" y="52.578" size="1.778" layer="96"/>
</instance>
<instance part="1X9_P5" gate="1" x="187.96" y="53.34" smashed="yes">
<attribute name="NAME" x="184.277" y="52.6542" size="1.778" layer="95"/>
<attribute name="VALUE" x="186.817" y="50.038" size="1.778" layer="96"/>
</instance>
<instance part="1X9_P6" gate="1" x="187.96" y="50.8" smashed="yes">
<attribute name="NAME" x="184.277" y="50.1142" size="1.778" layer="95"/>
<attribute name="VALUE" x="186.817" y="47.498" size="1.778" layer="96"/>
</instance>
<instance part="1X9_P7" gate="1" x="187.96" y="48.26" smashed="yes">
<attribute name="NAME" x="184.277" y="47.5742" size="1.778" layer="95"/>
<attribute name="VALUE" x="186.817" y="44.958" size="1.778" layer="96"/>
</instance>
<instance part="1X9_P8" gate="1" x="187.96" y="45.72" smashed="yes">
<attribute name="NAME" x="184.277" y="45.0342" size="1.778" layer="95"/>
<attribute name="VALUE" x="186.817" y="42.418" size="1.778" layer="96"/>
</instance>
<instance part="1X9_P9" gate="1" x="187.96" y="43.18" smashed="yes">
<attribute name="NAME" x="184.277" y="42.4942" size="1.778" layer="95"/>
<attribute name="VALUE" x="186.817" y="39.878" size="1.778" layer="96"/>
</instance>
<instance part="1X9_P10" gate="1" x="187.96" y="40.64" smashed="yes">
<attribute name="NAME" x="183.007" y="39.9542" size="1.778" layer="95"/>
<attribute name="VALUE" x="186.817" y="37.338" size="1.778" layer="96"/>
</instance>
<instance part="1X9_P11" gate="1" x="187.96" y="38.1" smashed="yes">
<attribute name="NAME" x="183.007" y="37.4142" size="1.778" layer="95"/>
<attribute name="VALUE" x="186.817" y="34.798" size="1.778" layer="96"/>
</instance>
<instance part="1X9_P12" gate="1" x="187.96" y="35.56" smashed="yes">
<attribute name="NAME" x="183.007" y="34.8742" size="1.778" layer="95"/>
<attribute name="VALUE" x="186.817" y="32.258" size="1.778" layer="96"/>
</instance>
<instance part="1X9_P13" gate="1" x="187.96" y="33.02" smashed="yes">
<attribute name="NAME" x="182.753" y="32.3342" size="1.778" layer="95"/>
<attribute name="VALUE" x="186.817" y="29.718" size="1.778" layer="96"/>
</instance>
<instance part="1X9_P14" gate="1" x="187.96" y="30.48" smashed="yes">
<attribute name="NAME" x="182.753" y="30.0482" size="1.778" layer="95"/>
<attribute name="VALUE" x="186.817" y="27.178" size="1.778" layer="96"/>
</instance>
<instance part="1X9_P15" gate="1" x="187.96" y="27.94" smashed="yes">
<attribute name="NAME" x="182.753" y="27.5082" size="1.778" layer="95"/>
<attribute name="VALUE" x="186.817" y="24.638" size="1.778" layer="96"/>
</instance>
<instance part="1X9_P16" gate="1" x="187.96" y="25.4" smashed="yes">
<attribute name="NAME" x="182.753" y="25.2222" size="1.778" layer="95"/>
<attribute name="VALUE" x="186.817" y="22.098" size="1.778" layer="96"/>
</instance>
</instances>
<busses>
</busses>
<nets>
<net name="S$4" class="0">
<segment>
<pinref part="H1" gate="A" pin="2"/>
<wire x1="88.9" y1="53.34" x2="96.52" y2="53.34" width="0.1524" layer="91"/>
<wire x1="96.52" y1="53.34" x2="96.52" y2="60.96" width="0.1524" layer="91"/>
<wire x1="96.52" y1="60.96" x2="104.14" y2="60.96" width="0.1524" layer="91"/>
<pinref part="P2" gate="1" pin="P"/>
<pinref part="LCD1" gate="G$1" pin="VCC"/>
<wire x1="0" y1="88.9" x2="0" y2="86.36" width="0.1524" layer="91"/>
<wire x1="0" y1="86.36" x2="96.52" y2="86.36" width="0.1524" layer="91"/>
<wire x1="96.52" y1="86.36" x2="96.52" y2="60.96" width="0.1524" layer="91"/>
<junction x="96.52" y="60.96"/>
</segment>
</net>
<net name="S$18" class="0">
<segment>
<pinref part="H1" gate="A" pin="4"/>
<wire x1="88.9" y1="50.8" x2="99.06" y2="50.8" width="0.1524" layer="91"/>
<wire x1="99.06" y1="50.8" x2="99.06" y2="55.88" width="0.1524" layer="91"/>
<wire x1="99.06" y1="55.88" x2="104.14" y2="55.88" width="0.1524" layer="91"/>
<pinref part="P4" gate="1" pin="P"/>
<pinref part="LCD1" gate="G$1" pin="RS"/>
<wire x1="5.08" y1="88.9" x2="5.08" y2="83.82" width="0.1524" layer="91"/>
<wire x1="5.08" y1="83.82" x2="99.06" y2="83.82" width="0.1524" layer="91"/>
<wire x1="99.06" y1="83.82" x2="99.06" y2="55.88" width="0.1524" layer="91"/>
<junction x="99.06" y="55.88"/>
</segment>
</net>
<net name="S$20" class="0">
<segment>
<pinref part="H1" gate="A" pin="8"/>
<wire x1="88.9" y1="45.72" x2="101.6" y2="45.72" width="0.1524" layer="91"/>
<pinref part="P8" gate="1" pin="P"/>
<pinref part="LCD1" gate="G$1" pin="D1"/>
<wire x1="101.6" y1="45.72" x2="104.14" y2="45.72" width="0.1524" layer="91"/>
<wire x1="15.24" y1="88.9" x2="15.24" y2="5.08" width="0.1524" layer="91"/>
<wire x1="15.24" y1="5.08" x2="101.6" y2="5.08" width="0.1524" layer="91"/>
<wire x1="101.6" y1="5.08" x2="101.6" y2="45.72" width="0.1524" layer="91"/>
<junction x="101.6" y="45.72"/>
</segment>
</net>
<net name="S$22" class="0">
<segment>
<pinref part="H1" gate="A" pin="10"/>
<wire x1="88.9" y1="43.18" x2="99.06" y2="43.18" width="0.1524" layer="91"/>
<wire x1="99.06" y1="43.18" x2="99.06" y2="40.64" width="0.1524" layer="91"/>
<wire x1="99.06" y1="40.64" x2="104.14" y2="40.64" width="0.1524" layer="91"/>
<pinref part="P10" gate="1" pin="P"/>
<pinref part="LCD1" gate="G$1" pin="D3"/>
<wire x1="20.32" y1="88.9" x2="20.32" y2="7.62" width="0.1524" layer="91"/>
<wire x1="20.32" y1="7.62" x2="99.06" y2="7.62" width="0.1524" layer="91"/>
<wire x1="99.06" y1="7.62" x2="99.06" y2="40.64" width="0.1524" layer="91"/>
<junction x="99.06" y="40.64"/>
</segment>
</net>
<net name="S$6" class="0">
<segment>
<pinref part="H1" gate="A" pin="6"/>
<wire x1="88.9" y1="48.26" x2="101.6" y2="48.26" width="0.1524" layer="91"/>
<wire x1="101.6" y1="48.26" x2="101.6" y2="50.8" width="0.1524" layer="91"/>
<wire x1="101.6" y1="50.8" x2="104.14" y2="50.8" width="0.1524" layer="91"/>
<pinref part="P6" gate="1" pin="P"/>
<pinref part="LCD1" gate="G$1" pin="E"/>
<wire x1="10.16" y1="88.9" x2="10.16" y2="81.28" width="0.1524" layer="91"/>
<wire x1="10.16" y1="81.28" x2="101.6" y2="81.28" width="0.1524" layer="91"/>
<wire x1="101.6" y1="81.28" x2="101.6" y2="50.8" width="0.1524" layer="91"/>
<junction x="101.6" y="50.8"/>
</segment>
</net>
<net name="S$21" class="0">
<segment>
<pinref part="H1" gate="A" pin="12"/>
<wire x1="88.9" y1="40.64" x2="96.52" y2="40.64" width="0.1524" layer="91"/>
<wire x1="96.52" y1="40.64" x2="96.52" y2="35.56" width="0.1524" layer="91"/>
<wire x1="96.52" y1="35.56" x2="104.14" y2="35.56" width="0.1524" layer="91"/>
<pinref part="P12" gate="1" pin="P"/>
<pinref part="LCD1" gate="G$1" pin="D5"/>
<wire x1="25.4" y1="88.9" x2="25.4" y2="10.16" width="0.1524" layer="91"/>
<wire x1="25.4" y1="10.16" x2="96.52" y2="10.16" width="0.1524" layer="91"/>
<wire x1="96.52" y1="10.16" x2="96.52" y2="35.56" width="0.1524" layer="91"/>
<junction x="96.52" y="35.56"/>
</segment>
</net>
<net name="S$23" class="0">
<segment>
<pinref part="H1" gate="A" pin="14"/>
<wire x1="88.9" y1="38.1" x2="93.98" y2="38.1" width="0.1524" layer="91"/>
<wire x1="93.98" y1="38.1" x2="93.98" y2="30.48" width="0.1524" layer="91"/>
<wire x1="93.98" y1="30.48" x2="104.14" y2="30.48" width="0.1524" layer="91"/>
<pinref part="P14" gate="1" pin="P"/>
<pinref part="LCD1" gate="G$1" pin="D7"/>
<wire x1="30.48" y1="88.9" x2="30.48" y2="12.7" width="0.1524" layer="91"/>
<wire x1="30.48" y1="12.7" x2="93.98" y2="12.7" width="0.1524" layer="91"/>
<wire x1="93.98" y1="12.7" x2="93.98" y2="30.48" width="0.1524" layer="91"/>
<junction x="93.98" y="30.48"/>
</segment>
</net>
<net name="S$24" class="0">
<segment>
<pinref part="H1" gate="A" pin="16"/>
<wire x1="88.9" y1="35.56" x2="91.44" y2="35.56" width="0.1524" layer="91"/>
<wire x1="91.44" y1="35.56" x2="91.44" y2="25.4" width="0.1524" layer="91"/>
<wire x1="91.44" y1="25.4" x2="104.14" y2="25.4" width="0.1524" layer="91"/>
<pinref part="P16" gate="1" pin="P"/>
<pinref part="LCD1" gate="G$1" pin="NC@2"/>
<wire x1="35.56" y1="88.9" x2="35.56" y2="25.4" width="0.1524" layer="91"/>
<wire x1="35.56" y1="25.4" x2="91.44" y2="25.4" width="0.1524" layer="91"/>
<junction x="91.44" y="25.4"/>
</segment>
</net>
<net name="S$1" class="0">
<segment>
<pinref part="H1" gate="A" pin="1"/>
<wire x1="81.28" y1="53.34" x2="71.12" y2="53.34" width="0.1524" layer="91"/>
<wire x1="71.12" y1="53.34" x2="71.12" y2="63.5" width="0.1524" layer="91"/>
<wire x1="71.12" y1="63.5" x2="104.14" y2="63.5" width="0.1524" layer="91"/>
<pinref part="P1" gate="1" pin="P"/>
<pinref part="LCD1" gate="G$1" pin="GND"/>
<wire x1="71.12" y1="53.34" x2="-2.54" y2="53.34" width="0.1524" layer="91"/>
<wire x1="-2.54" y1="53.34" x2="-2.54" y2="88.9" width="0.1524" layer="91"/>
<junction x="71.12" y="53.34"/>
</segment>
</net>
<net name="S$3" class="0">
<segment>
<pinref part="H1" gate="A" pin="3"/>
<wire x1="81.28" y1="50.8" x2="68.58" y2="50.8" width="0.1524" layer="91"/>
<wire x1="68.58" y1="50.8" x2="68.58" y2="71.12" width="0.1524" layer="91"/>
<wire x1="68.58" y1="71.12" x2="111.76" y2="71.12" width="0.1524" layer="91"/>
<wire x1="111.76" y1="71.12" x2="111.76" y2="58.42" width="0.1524" layer="91"/>
<pinref part="P3" gate="1" pin="P"/>
<wire x1="111.76" y1="58.42" x2="109.22" y2="58.42" width="0.1524" layer="91"/>
<pinref part="LCD1" gate="G$1" pin="CONTR"/>
<wire x1="2.54" y1="88.9" x2="2.54" y2="50.8" width="0.1524" layer="91"/>
<wire x1="2.54" y1="50.8" x2="68.58" y2="50.8" width="0.1524" layer="91"/>
<junction x="68.58" y="50.8"/>
<wire x1="106.68" y1="58.42" x2="111.76" y2="58.42" width="0.1524" layer="91"/>
<junction x="111.76" y="58.42"/>
<wire x1="111.76" y1="58.42" x2="187.96" y2="58.42" width="0.1524" layer="91"/>
</segment>
</net>
<net name="S$15" class="0">
<segment>
<pinref part="H1" gate="A" pin="15"/>
<wire x1="81.28" y1="35.56" x2="73.66" y2="35.56" width="0.1524" layer="91"/>
<wire x1="73.66" y1="35.56" x2="73.66" y2="27.94" width="0.1524" layer="91"/>
<wire x1="73.66" y1="27.94" x2="104.14" y2="27.94" width="0.1524" layer="91"/>
<pinref part="P15" gate="1" pin="P"/>
<pinref part="LCD1" gate="G$1" pin="NC@1"/>
<wire x1="33.02" y1="88.9" x2="33.02" y2="35.56" width="0.1524" layer="91"/>
<wire x1="33.02" y1="35.56" x2="73.66" y2="35.56" width="0.1524" layer="91"/>
<junction x="73.66" y="35.56"/>
</segment>
</net>
<net name="S$13" class="0">
<segment>
<pinref part="H1" gate="A" pin="13"/>
<wire x1="81.28" y1="38.1" x2="71.12" y2="38.1" width="0.1524" layer="91"/>
<wire x1="71.12" y1="38.1" x2="71.12" y2="20.32" width="0.1524" layer="91"/>
<wire x1="71.12" y1="20.32" x2="111.76" y2="20.32" width="0.1524" layer="91"/>
<wire x1="111.76" y1="20.32" x2="111.76" y2="33.02" width="0.1524" layer="91"/>
<wire x1="111.76" y1="33.02" x2="109.22" y2="33.02" width="0.1524" layer="91"/>
<pinref part="P13" gate="1" pin="P"/>
<pinref part="LCD1" gate="G$1" pin="D6"/>
<wire x1="27.94" y1="88.9" x2="27.94" y2="38.1" width="0.1524" layer="91"/>
<wire x1="27.94" y1="38.1" x2="71.12" y2="38.1" width="0.1524" layer="91"/>
<junction x="71.12" y="38.1"/>
<wire x1="111.76" y1="33.02" x2="187.96" y2="33.02" width="0.1524" layer="91"/>
<junction x="111.76" y="33.02"/>
</segment>
</net>
<net name="S$11" class="0">
<segment>
<pinref part="H1" gate="A" pin="11"/>
<wire x1="81.28" y1="40.64" x2="68.58" y2="40.64" width="0.1524" layer="91"/>
<wire x1="68.58" y1="40.64" x2="68.58" y2="17.78" width="0.1524" layer="91"/>
<wire x1="68.58" y1="17.78" x2="114.3" y2="17.78" width="0.1524" layer="91"/>
<wire x1="114.3" y1="17.78" x2="114.3" y2="38.1" width="0.1524" layer="91"/>
<wire x1="114.3" y1="38.1" x2="109.22" y2="38.1" width="0.1524" layer="91"/>
<pinref part="P11" gate="1" pin="P"/>
<pinref part="LCD1" gate="G$1" pin="D4"/>
<wire x1="22.86" y1="88.9" x2="22.86" y2="40.64" width="0.1524" layer="91"/>
<wire x1="22.86" y1="40.64" x2="68.58" y2="40.64" width="0.1524" layer="91"/>
<junction x="68.58" y="40.64"/>
<wire x1="114.3" y1="38.1" x2="187.96" y2="38.1" width="0.1524" layer="91"/>
<junction x="114.3" y="38.1"/>
</segment>
</net>
<net name="S$9" class="0">
<segment>
<pinref part="H1" gate="A" pin="9"/>
<wire x1="81.28" y1="43.18" x2="66.04" y2="43.18" width="0.1524" layer="91"/>
<wire x1="66.04" y1="43.18" x2="66.04" y2="15.24" width="0.1524" layer="91"/>
<wire x1="66.04" y1="15.24" x2="116.84" y2="15.24" width="0.1524" layer="91"/>
<wire x1="116.84" y1="15.24" x2="116.84" y2="43.18" width="0.1524" layer="91"/>
<wire x1="116.84" y1="43.18" x2="109.22" y2="43.18" width="0.1524" layer="91"/>
<pinref part="P9" gate="1" pin="P"/>
<pinref part="LCD1" gate="G$1" pin="D2"/>
<wire x1="17.78" y1="88.9" x2="17.78" y2="43.18" width="0.1524" layer="91"/>
<wire x1="17.78" y1="43.18" x2="66.04" y2="43.18" width="0.1524" layer="91"/>
<junction x="66.04" y="43.18"/>
<wire x1="116.84" y1="43.18" x2="187.96" y2="43.18" width="0.1524" layer="91"/>
<junction x="116.84" y="43.18"/>
</segment>
</net>
<net name="S$5" class="0">
<segment>
<pinref part="H1" gate="A" pin="5"/>
<wire x1="81.28" y1="48.26" x2="66.04" y2="48.26" width="0.1524" layer="91"/>
<wire x1="66.04" y1="48.26" x2="66.04" y2="73.66" width="0.1524" layer="91"/>
<wire x1="66.04" y1="73.66" x2="114.3" y2="73.66" width="0.1524" layer="91"/>
<wire x1="114.3" y1="73.66" x2="114.3" y2="53.34" width="0.1524" layer="91"/>
<wire x1="114.3" y1="53.34" x2="109.22" y2="53.34" width="0.1524" layer="91"/>
<pinref part="P5" gate="1" pin="P"/>
<pinref part="LCD1" gate="G$1" pin="R/W"/>
<wire x1="7.62" y1="88.9" x2="7.62" y2="48.26" width="0.1524" layer="91"/>
<wire x1="7.62" y1="48.26" x2="66.04" y2="48.26" width="0.1524" layer="91"/>
<junction x="66.04" y="48.26"/>
<wire x1="114.3" y1="53.34" x2="187.96" y2="53.34" width="0.1524" layer="91"/>
<junction x="114.3" y="53.34"/>
</segment>
</net>
<net name="S$7" class="0">
<segment>
<pinref part="H1" gate="A" pin="7"/>
<wire x1="81.28" y1="45.72" x2="63.5" y2="45.72" width="0.1524" layer="91"/>
<wire x1="63.5" y1="45.72" x2="63.5" y2="76.2" width="0.1524" layer="91"/>
<wire x1="63.5" y1="76.2" x2="116.84" y2="76.2" width="0.1524" layer="91"/>
<wire x1="116.84" y1="76.2" x2="116.84" y2="48.26" width="0.1524" layer="91"/>
<wire x1="116.84" y1="48.26" x2="109.22" y2="48.26" width="0.1524" layer="91"/>
<pinref part="P7" gate="1" pin="P"/>
<pinref part="LCD1" gate="G$1" pin="D0"/>
<wire x1="12.7" y1="88.9" x2="12.7" y2="45.72" width="0.1524" layer="91"/>
<wire x1="12.7" y1="45.72" x2="63.5" y2="45.72" width="0.1524" layer="91"/>
<junction x="63.5" y="45.72"/>
<wire x1="116.84" y1="48.26" x2="187.96" y2="48.26" width="0.1524" layer="91"/>
<junction x="116.84" y="48.26"/>
</segment>
</net>
<net name="S$2" class="0">
<segment>
<pinref part="H2" gate="A" pin="1"/>
<wire x1="190.5" y1="63.5" x2="210.82" y2="63.5" width="0.1524" layer="91"/>
<pinref part="1X9_P1" gate="1" pin="P"/>
</segment>
</net>
<net name="S$8" class="0">
<segment>
<pinref part="H2" gate="A" pin="2"/>
<wire x1="190.5" y1="60.96" x2="210.82" y2="60.96" width="0.1524" layer="91"/>
<pinref part="1X9_P2" gate="1" pin="P"/>
</segment>
</net>
<net name="S$10" class="0">
<segment>
<pinref part="H2" gate="A" pin="3"/>
<wire x1="190.5" y1="58.42" x2="210.82" y2="58.42" width="0.1524" layer="91"/>
<pinref part="1X9_P3" gate="1" pin="P"/>
</segment>
</net>
<net name="S$12" class="0">
<segment>
<pinref part="H2" gate="A" pin="4"/>
<wire x1="190.5" y1="55.88" x2="210.82" y2="55.88" width="0.1524" layer="91"/>
<pinref part="1X9_P4" gate="1" pin="P"/>
</segment>
</net>
<net name="S$14" class="0">
<segment>
<pinref part="H2" gate="A" pin="5"/>
<wire x1="190.5" y1="53.34" x2="210.82" y2="53.34" width="0.1524" layer="91"/>
<pinref part="1X9_P5" gate="1" pin="P"/>
</segment>
</net>
<net name="S$16" class="0">
<segment>
<pinref part="H2" gate="A" pin="6"/>
<wire x1="190.5" y1="50.8" x2="210.82" y2="50.8" width="0.1524" layer="91"/>
<pinref part="1X9_P6" gate="1" pin="P"/>
</segment>
</net>
<net name="S$17" class="0">
<segment>
<pinref part="H2" gate="A" pin="7"/>
<wire x1="190.5" y1="48.26" x2="210.82" y2="48.26" width="0.1524" layer="91"/>
<pinref part="1X9_P7" gate="1" pin="P"/>
</segment>
</net>
<net name="S$19" class="0">
<segment>
<pinref part="H2" gate="A" pin="8"/>
<wire x1="190.5" y1="45.72" x2="210.82" y2="45.72" width="0.1524" layer="91"/>
<pinref part="1X9_P8" gate="1" pin="P"/>
</segment>
</net>
<net name="S$25" class="0">
<segment>
<pinref part="H2" gate="A" pin="9"/>
<wire x1="190.5" y1="43.18" x2="210.82" y2="43.18" width="0.1524" layer="91"/>
<pinref part="1X9_P9" gate="1" pin="P"/>
</segment>
</net>
<net name="S$26" class="0">
<segment>
<pinref part="H2" gate="A" pin="10"/>
<wire x1="190.5" y1="40.64" x2="210.82" y2="40.64" width="0.1524" layer="91"/>
<pinref part="1X9_P10" gate="1" pin="P"/>
</segment>
</net>
<net name="S$27" class="0">
<segment>
<pinref part="H2" gate="A" pin="11"/>
<wire x1="190.5" y1="38.1" x2="210.82" y2="38.1" width="0.1524" layer="91"/>
<pinref part="1X9_P11" gate="1" pin="P"/>
</segment>
</net>
<net name="S$28" class="0">
<segment>
<pinref part="H2" gate="A" pin="12"/>
<wire x1="190.5" y1="35.56" x2="210.82" y2="35.56" width="0.1524" layer="91"/>
<pinref part="1X9_P12" gate="1" pin="P"/>
</segment>
</net>
<net name="S$29" class="0">
<segment>
<pinref part="H2" gate="A" pin="13"/>
<wire x1="190.5" y1="33.02" x2="210.82" y2="33.02" width="0.1524" layer="91"/>
<pinref part="1X9_P13" gate="1" pin="P"/>
</segment>
</net>
<net name="S$30" class="0">
<segment>
<pinref part="H2" gate="A" pin="14"/>
<wire x1="190.5" y1="30.48" x2="210.82" y2="30.48" width="0.1524" layer="91"/>
<pinref part="1X9_P14" gate="1" pin="P"/>
</segment>
</net>
<net name="S$31" class="0">
<segment>
<pinref part="H2" gate="A" pin="15"/>
<wire x1="190.5" y1="27.94" x2="210.82" y2="27.94" width="0.1524" layer="91"/>
<pinref part="1X9_P15" gate="1" pin="P"/>
</segment>
</net>
<net name="S$32" class="0">
<segment>
<pinref part="H2" gate="A" pin="16"/>
<wire x1="190.5" y1="25.4" x2="210.82" y2="25.4" width="0.1524" layer="91"/>
<pinref part="1X9_P16" gate="1" pin="P"/>
</segment>
</net>
<net name="N$1" class="0">
<segment>
<wire x1="106.68" y1="63.5" x2="187.96" y2="63.5" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$2" class="0">
<segment>
<wire x1="106.68" y1="60.96" x2="187.96" y2="60.96" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$4" class="0">
<segment>
<wire x1="106.68" y1="55.88" x2="187.96" y2="55.88" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$5" class="0">
<segment>
<wire x1="106.68" y1="50.8" x2="187.96" y2="50.8" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$6" class="0">
<segment>
<wire x1="106.68" y1="45.72" x2="187.96" y2="45.72" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$7" class="0">
<segment>
<wire x1="106.68" y1="40.64" x2="187.96" y2="40.64" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$8" class="0">
<segment>
<wire x1="106.68" y1="35.56" x2="187.96" y2="35.56" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$9" class="0">
<segment>
<wire x1="106.68" y1="30.48" x2="187.96" y2="30.48" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$10" class="0">
<segment>
<wire x1="106.68" y1="27.94" x2="187.96" y2="27.94" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$11" class="0">
<segment>
<wire x1="106.68" y1="25.4" x2="187.96" y2="25.4" width="0.1524" layer="91"/>
</segment>
</net>
</nets>
</sheet>
</sheets>
</schematic>
</drawing>
<compatibility>
<note version="6.3" minversion="6.2.2" severity="warning">
Since Version 6.2.2 text objects can contain more than one line,
which will not be processed correctly with this version.
</note>
</compatibility>
</eagle>

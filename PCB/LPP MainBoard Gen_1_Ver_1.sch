<?xml version="1.0" encoding="utf-8"?>
<!DOCTYPE eagle SYSTEM "eagle.dtd">
<eagle version="7.5.0">
<drawing>
<settings>
<setting alwaysvectorfont="no"/>
<setting verticaltext="up"/>
</settings>
<grid distance="0.1" unitdist="inch" unit="mil" style="lines" multiple="1" display="yes" altdistance="0.01" altunitdist="inch" altunit="inch"/>
<layers>
<layer number="1" name="Top" color="4" fill="1" visible="no" active="no"/>
<layer number="2" name="Route2" color="1" fill="3" visible="no" active="no"/>
<layer number="3" name="Route3" color="4" fill="3" visible="no" active="no"/>
<layer number="4" name="Route4" color="1" fill="4" visible="no" active="no"/>
<layer number="5" name="Route5" color="4" fill="4" visible="no" active="no"/>
<layer number="6" name="Route6" color="1" fill="8" visible="no" active="no"/>
<layer number="7" name="Route7" color="4" fill="8" visible="no" active="no"/>
<layer number="8" name="Route8" color="1" fill="2" visible="no" active="no"/>
<layer number="9" name="Route9" color="4" fill="2" visible="no" active="no"/>
<layer number="10" name="Route10" color="1" fill="7" visible="no" active="no"/>
<layer number="11" name="Route11" color="4" fill="7" visible="no" active="no"/>
<layer number="12" name="Route12" color="1" fill="5" visible="no" active="no"/>
<layer number="13" name="Route13" color="4" fill="5" visible="no" active="no"/>
<layer number="14" name="Route14" color="1" fill="6" visible="no" active="no"/>
<layer number="15" name="Route15" color="4" fill="6" visible="no" active="no"/>
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
<layer number="46" name="Milling" color="3" fill="1" visible="yes" active="no"/>
<layer number="47" name="Measures" color="7" fill="1" visible="no" active="no"/>
<layer number="48" name="Document" color="7" fill="1" visible="no" active="no"/>
<layer number="49" name="Reference" color="7" fill="1" visible="no" active="no"/>
<layer number="51" name="tDocu" color="7" fill="1" visible="no" active="no"/>
<layer number="52" name="bDocu" color="7" fill="1" visible="no" active="no"/>
<layer number="90" name="Modules" color="5" fill="1" visible="yes" active="yes"/>
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
<attributes/>
<variantdefs/>
<libraries>
<library name="common">
<packages>
<package name="USB-1_TYPE_B">
<pad name="3" x="-1.3" y="2.66" drill="0.9" diameter="1.6" rot="R0" stop="yes" thermals="no"/>
<pad name="4" x="1.2" y="2.66" drill="0.9" diameter="1.6" rot="R0" stop="yes" thermals="no"/>
<pad name="1" x="1.2" y="4.66" drill="0.9" shape="square" diameter="1.6" rot="R0" stop="yes" thermals="no"/>
<pad name="2" x="-1.3" y="4.66" drill="0.9" diameter="1.6" rot="R0" stop="yes" thermals="no"/>
<pad name="5" x="-6.07" y="-0.05" drill="2" diameter="3.3" rot="R0" stop="yes" thermals="no"/>
<pad name="6" x="5.97" y="-0.05" drill="2" diameter="3.3" rot="R0" stop="yes" thermals="no"/>
<wire layer="21" width="0.12" x1="-6.195" y1="5.785" x2="6.095" y2="5.785"/>
<wire layer="21" width="0.12" x1="6.095" y1="5.785" x2="6.095" y2="1.776"/>
<wire layer="51" width="0.12" x1="-6.195" y1="5.785" x2="5.095" y2="5.785"/>
<wire layer="51" width="0.12" x1="5.095" y1="5.785" x2="6.095" y2="4.785"/>
<wire layer="51" width="0.12" x1="6.095" y1="4.785" x2="6.095" y2="-10.465"/>
<wire layer="51" width="0.12" x1="6.095" y1="-10.465" x2="-6.195" y2="-10.465"/>
<wire layer="51" width="0.12" x1="-6.195" y1="-10.465" x2="-6.195" y2="5.785"/>
<wire layer="21" width="0.12" x1="6.095" y1="-1.876" x2="6.095" y2="-10.465"/>
<wire layer="21" width="0.12" x1="6.095" y1="-10.465" x2="-6.195" y2="-10.465"/>
<wire layer="21" width="0.12" x1="-6.195" y1="-10.465" x2="-6.195" y2="-1.876"/>
<wire layer="21" width="0.12" x1="-6.195" y1="1.776" x2="-6.195" y2="5.785"/>
<circle layer="21" x="1.2" y="6.215" radius="0.25" width="0"/>
</package>
<package name="R_0805_1206">
<smd name="1@_1" x="-0.9" y="0" layer="1" dx="1.21" dy="1.57" roundness="41" rot="R0" stop="yes" cream="yes" thermals="no"/>
<smd name="2@_1" x="0.9" y="0" layer="1" dx="1.21" dy="1.57" roundness="41" rot="R180" stop="yes" cream="yes" thermals="no"/>
<smd name="1@" x="-1.525" y="0" layer="1" dx="1.26" dy="1.92" roundness="40" rot="R0" stop="yes" cream="yes" thermals="no"/>
<smd name="2@" x="1.525" y="0" layer="1" dx="1.26" dy="1.92" roundness="40" rot="R180" stop="yes" cream="yes" thermals="no"/>
<wire layer="51" width="0.12" x1="-2.5" y1="1.27" x2="2.5" y2="1.27"/>
<wire layer="51" width="0.12" x1="2.5" y1="1.27" x2="2.5" y2="-1.27"/>
<wire layer="51" width="0.12" x1="2.5" y1="-1.27" x2="-2.5" y2="-1.27"/>
<wire layer="51" width="0.12" x1="-2.5" y1="-1.27" x2="-2.5" y2="1.27"/>
<wire layer="21" width="0.15" x1="-0.67" y1="1.059" x2="0.67" y2="1.059"/>
<wire layer="21" width="0.15" x1="-0.67" y1="-1.005" x2="0.67" y2="-1.005"/>
</package>
<package name="PLS_2">
<description>LINK: &lt;a href="http://vinratel.at.ua/"&gt;http://vinratel.at.ua/&lt;/a&gt;
author: &lt;a href="&#1044;&#1072;&#1085;&#1100;&#1082;&#1086;&#1074;&#1089;&#1082;&#1080;&#1081; &#1042;.&#1048;."&gt;&#1044;&#1072;&#1085;&#1100;&#1082;&#1086;&#1074;&#1089;&#1082;&#1080;&#1081; &#1042;.&#1048;.&lt;/a&gt;
mail: dvi534538@mail/ru</description>
<pad name="1" x="-1.27" y="0" drill="0.9" shape="square" diameter="2" rot="R0" stop="yes" thermals="no"/>
<pad name="2" x="1.27" y="0" drill="0.9" diameter="2" rot="R0" stop="yes" thermals="no"/>
<wire layer="21" width="0.25" x1="2.54" y1="-1.27" x2="2.54" y2="1.27"/>
<wire layer="21" width="0.25" x1="-2.54" y1="-1.27" x2="2.54" y2="-1.27"/>
<wire layer="21" width="0.25" x1="-2.54" y1="-1.27" x2="-2.54" y2="1.27"/>
<wire layer="21" width="0.25" x1="-2.54" y1="1.27" x2="2.54" y2="1.27"/>
</package>
<package name="USB-1_TYPE_A">
<pad name="1" x="-3.5" y="1.3" drill="0.9" shape="square" diameter="1.6" rot="R0" stop="yes" thermals="no"/>
<pad name="2" x="-1" y="1.3" drill="0.9" diameter="1.6" rot="R0" stop="yes" thermals="no"/>
<pad name="3" x="1" y="1.3" drill="0.9" diameter="1.6" rot="R0" stop="yes" thermals="no"/>
<pad name="4" x="3.5" y="1.3" drill="0.9" diameter="1.6" rot="R0" stop="yes" thermals="no"/>
<pad name="5@_1" x="-6.57" y="-1.41" drill="2" diameter="3.3" rot="R0" stop="yes" thermals="no"/>
<pad name="5@" x="6.57" y="-1.41" drill="2" diameter="3.5" rot="R0" stop="yes" thermals="no"/>
<wire layer="21" width="0.12" x1="-0.95" y1="-3" x2="-0.95" y2="-3.7"/>
<wire layer="21" width="0.12" x1="-0.95" y1="-3.7" x2="-5.76" y2="-3.7"/>
<wire layer="21" width="0.12" x1="-5.76" y1="-3.7" x2="-5.76" y2="-3.162"/>
<wire layer="21" width="0.12" x1="-6.191" y1="3.018" x2="-5.76" y2="3.02"/>
<wire layer="21" width="0.12" x1="-5.76" y1="3.02" x2="-5.76" y2="3.72"/>
<wire layer="21" width="0.12" x1="-5.76" y1="3.72" x2="-0.95" y2="3.72"/>
<wire layer="21" width="0.12" x1="-0.95" y1="3.72" x2="-0.95" y2="3.04"/>
<wire layer="21" width="0.12" x1="-0.95" y1="3.04" x2="0.908" y2="3.04"/>
<wire layer="21" width="0.12" x1="0.908" y1="3.04" x2="0.908" y2="3.72"/>
<wire layer="21" width="0.12" x1="0.908" y1="3.72" x2="5.76" y2="3.72"/>
<wire layer="21" width="0.12" x1="5.76" y1="3.72" x2="5.76" y2="3.02"/>
<wire layer="21" width="0.12" x1="5.76" y1="3.02" x2="6.19" y2="3.02"/>
<wire layer="21" width="0.12" x1="6.698" y1="2.511" x2="6.7" y2="2.08"/>
<wire layer="21" width="0.12" x1="6.7" y1="2.08" x2="7.4" y2="2.08"/>
<wire layer="21" width="0.12" x1="7.4" y1="2.08" x2="7.4" y2="0.332"/>
<wire layer="21" width="0.12" x1="5.76" y1="-3.162" x2="5.76" y2="-3.7"/>
<wire layer="21" width="0.12" x1="5.76" y1="-3.7" x2="0.944" y2="-3.7"/>
<wire layer="21" width="0.12" x1="0.944" y1="-3.7" x2="0.944" y2="-3"/>
<wire layer="21" width="0.12" x1="0.944" y1="-3" x2="-0.944" y2="-3"/>
<wire layer="21" width="0.12" x1="-7.4" y1="0.332" x2="-7.4" y2="2.08"/>
<wire layer="21" width="0.12" x1="-7.4" y1="2.08" x2="-6.7" y2="2.08"/>
<wire layer="21" width="0.12" x1="-6.7" y1="2.08" x2="-6.699" y2="2.438"/>
<wire layer="21" width="0.12" x1="-6.191" y1="3.018" x2="-6.698" y2="2.42" curve="90.96175"/>
<wire layer="21" width="0.12" x1="6.698" y1="2.511" x2="6.1" y2="3.018" curve="90.955893"/>
<circle layer="21" x="-3.5" y="4.15" radius="0.25" width="0"/>
<wire layer="51" width="0.12" x1="-0.95" y1="-3" x2="-0.95" y2="-3.7"/>
<wire layer="51" width="0.12" x1="-0.95" y1="-3.7" x2="-5.76" y2="-3.7"/>
<wire layer="51" width="0.12" x1="-5.76" y1="-3.7" x2="-5.76" y2="-3"/>
<wire layer="51" width="0.12" x1="-5.76" y1="-3" x2="-6.11" y2="-3"/>
<wire layer="51" width="0.12" x1="-6.191" y1="3.018" x2="-5.76" y2="3.02"/>
<wire layer="51" width="0.12" x1="-5.76" y1="3.02" x2="-5.76" y2="3.72"/>
<wire layer="51" width="0.12" x1="-5.76" y1="3.72" x2="-0.95" y2="3.72"/>
<wire layer="51" width="0.12" x1="-0.95" y1="3.72" x2="-0.95" y2="3.04"/>
<wire layer="51" width="0.12" x1="-0.95" y1="3.04" x2="0.908" y2="3.04"/>
<wire layer="51" width="0.12" x1="0.908" y1="3.04" x2="0.908" y2="3.72"/>
<wire layer="51" width="0.12" x1="0.908" y1="3.72" x2="5.76" y2="3.72"/>
<wire layer="51" width="0.12" x1="5.76" y1="3.72" x2="5.76" y2="3.02"/>
<wire layer="51" width="0.12" x1="5.76" y1="3.02" x2="6.19" y2="3.02"/>
<wire layer="51" width="0.12" x1="6.698" y1="2.511" x2="6.7" y2="2.08"/>
<wire layer="51" width="0.12" x1="6.7" y1="2.08" x2="7.4" y2="2.08"/>
<wire layer="51" width="0.12" x1="7.4" y1="2.08" x2="7.4" y2="-2.004"/>
<wire layer="51" width="0.12" x1="7.4" y1="-2.004" x2="6.7" y2="-2.004"/>
<wire layer="51" width="0.12" x1="6.7" y1="-2.004" x2="6.698" y2="-2.4"/>
<wire layer="51" width="0.12" x1="6.22" y1="-3" x2="5.76" y2="-3"/>
<wire layer="51" width="0.12" x1="5.76" y1="-3" x2="5.76" y2="-3.7"/>
<wire layer="51" width="0.12" x1="5.76" y1="-3.7" x2="0.944" y2="-3.7"/>
<wire layer="51" width="0.12" x1="0.944" y1="-3.7" x2="0.944" y2="-3"/>
<wire layer="51" width="0.12" x1="0.944" y1="-3" x2="-0.944" y2="-3"/>
<wire layer="51" width="0.12" x1="-6.7" y1="-2.49" x2="-6.7" y2="-2.06"/>
<wire layer="51" width="0.12" x1="-6.7" y1="-2.06" x2="-7.4" y2="-2.06"/>
<wire layer="51" width="0.12" x1="-7.4" y1="-2.06" x2="-7.4" y2="2.08"/>
<wire layer="51" width="0.12" x1="-7.4" y1="2.08" x2="-6.7" y2="2.08"/>
<wire layer="51" width="0.12" x1="-6.7" y1="2.08" x2="-6.699" y2="2.438"/>
<wire layer="51" width="0.12" x1="-6.191" y1="3.018" x2="-6.698" y2="2.42" curve="90.96175"/>
<wire layer="51" width="0.12" x1="6.698" y1="2.511" x2="6.1" y2="3.018" curve="90.955893"/>
<wire layer="51" width="0.12" x1="6.191" y1="-2.999" x2="6.698" y2="-2.4" curve="90.96175"/>
<wire layer="51" width="0.12" x1="-6.694" y1="-2.5" x2="-6.101" y2="-3.003" curve="90.956171"/>
<wire layer="51" width="0.12" x1="-5.55" y1="1.89" x2="5.55" y2="1.89"/>
<wire layer="51" width="0.12" x1="5.55" y1="1.89" x2="5.55" y2="-0.01"/>
<wire layer="51" width="0.12" x1="5.55" y1="-0.01" x2="-5.55" y2="-0.01"/>
<wire layer="51" width="0.12" x1="-5.55" y1="-0.01" x2="-5.55" y2="1.89"/>
</package>
<package name="CAP_P_5MM">
<description>Unique Name: NTE_NPR_10.5H18_CAP</description>
<pad name="1" x="-2.5" y="0" drill="0.8" shape="square" diameter="1.6" rot="R0" stop="yes" thermals="no"/>
<pad name="2" x="2.5" y="0" drill="0.8" diameter="1.6" rot="R180" stop="yes" thermals="no"/>
<circle layer="21" x="0" y="0" radius="4" width="0.12"/>
</package>
<package name="CAP_P_3MM">
<pad name="1" x="-1.5" y="0" drill="0.8" shape="square" diameter="1.6" rot="R0" stop="yes" thermals="no"/>
<pad name="2" x="1.5" y="0" drill="0.8" diameter="1.6" rot="R180" stop="yes" thermals="no"/>
<circle layer="21" x="0" y="0" radius="2.75" width="0.12"/>
<circle layer="21" x="0" y="0" radius="2.75" width="0.12"/>
</package>
<package name="2_SCREW_TERM._BLK.">
<pad name="1" x="-2.54" y="0" drill="1" diameter="3.175" rot="R0" stop="yes" thermals="no"/>
<pad name="2" x="2.54" y="0" drill="1" diameter="3.175" rot="R0" stop="yes" thermals="no"/>
<wire layer="21" width="0.25" x1="-5.334" y1="5.055" x2="5.334" y2="5.055"/>
<wire layer="21" width="0.25" x1="5.334" y1="5.055" x2="5.334" y2="-4.445"/>
<wire layer="21" width="0.25" x1="5.334" y1="-4.445" x2="-5.334" y2="-4.445"/>
<wire layer="21" width="0.25" x1="-5.334" y1="-4.445" x2="-5.334" y2="5.055"/>
<wire layer="21" width="0.25" x1="-5.239" y1="-2.539" x2="5.239" y2="-2.539"/>
<circle layer="21" x="-2.541" y="3.048" radius="0.635" width="0"/>
<circle layer="21" x="2.54" y="3.048" radius="0.635" width="0"/>
</package>
<package name="PLS_3">
<description>LINK: &lt;a href="http://vinratel.at.ua/"&gt;http://vinratel.at.ua/&lt;/a&gt;
author: &lt;a href="&#1044;&#1072;&#1085;&#1100;&#1082;&#1086;&#1074;&#1089;&#1082;&#1080;&#1081; &#1042;.&#1048;."&gt;&#1044;&#1072;&#1085;&#1100;&#1082;&#1086;&#1074;&#1089;&#1082;&#1080;&#1081; &#1042;.&#1048;.&lt;/a&gt;
mail: dvi534538@mail/ru</description>
<pad name="1" x="-2.54" y="0" drill="0.9" shape="square" diameter="2" rot="R0" stop="yes" thermals="no"/>
<pad name="2" x="0" y="0" drill="0.9" diameter="2" rot="R0" stop="yes" thermals="no"/>
<pad name="3" x="2.54" y="0" drill="0.9" diameter="2" rot="R0" stop="yes" thermals="no"/>
<wire layer="21" width="0.25" x1="-3.81" y1="-1.27" x2="-3.81" y2="1.27"/>
<wire layer="21" width="0.25" x1="-3.81" y1="1.27" x2="3.81" y2="1.27"/>
<wire layer="21" width="0.25" x1="3.81" y1="-1.27" x2="3.81" y2="1.27"/>
<wire layer="21" width="0.25" x1="-3.81" y1="-1.27" x2="3.81" y2="-1.27"/>
</package>
<package name="СAP_P_SMD_5MM">
<smd name="1@" x="-2" y="0" layer="1" dx="1.26" dy="1.92" roundness="40" rot="R0" stop="yes" cream="yes" thermals="no"/>
<smd name="2@" x="2" y="0" layer="1" dx="1.26" dy="1.92" roundness="40" rot="R180" stop="yes" cream="yes" thermals="no"/>
<wire layer="51" width="0.12" x1="-2.817" y1="1.27" x2="2.857" y2="1.27"/>
<wire layer="51" width="0.12" x1="2.857" y1="1.27" x2="2.857" y2="-1.27"/>
<wire layer="51" width="0.12" x1="2.857" y1="-1.27" x2="-2.817" y2="-1.27"/>
<wire layer="51" width="0.12" x1="-2.817" y1="-1.27" x2="-2.817" y2="1.27"/>
<wire layer="21" width="0.15" x1="-3.016" y1="-0.722" x2="-3.016" y2="0.617"/>
</package>
<package name="ST_PILL">
<pad name="1" x="-7.015" y="24.128" drill="0.7" shape="square" diameter="1.2" rot="R270" stop="yes" thermals="no"/>
<pad name="2" x="-7.015" y="21.588" drill="0.7" diameter="1.2" rot="R270" stop="yes" thermals="no"/>
<pad name="3" x="-7.015" y="19.048" drill="0.7" diameter="1.2" rot="R270" stop="yes" thermals="no"/>
<pad name="4" x="-7.015" y="16.508" drill="0.7" diameter="1.2" rot="R270" stop="yes" thermals="no"/>
<pad name="5" x="-7.015" y="13.968" drill="0.7" diameter="1.2" rot="R270" stop="yes" thermals="no"/>
<pad name="6" x="-7.015" y="11.428" drill="0.7" diameter="1.2" rot="R270" stop="yes" thermals="no"/>
<pad name="7" x="-7.015" y="8.888" drill="0.7" diameter="1.2" rot="R270" stop="yes" thermals="no"/>
<pad name="8" x="-7.015" y="6.348" drill="0.7" diameter="1.2" rot="R270" stop="yes" thermals="no"/>
<pad name="9" x="-7.015" y="3.808" drill="0.7" diameter="1.2" rot="R270" stop="yes" thermals="no"/>
<pad name="10" x="-7.015" y="1.268" drill="0.7" diameter="1.2" rot="R270" stop="yes" thermals="no"/>
<pad name="11" x="-7.015" y="-1.272" drill="0.7" diameter="1.2" rot="R270" stop="yes" thermals="no"/>
<pad name="12" x="-7.015" y="-3.812" drill="0.7" diameter="1.2" rot="R270" stop="yes" thermals="no"/>
<pad name="13" x="-7.015" y="-6.352" drill="0.7" diameter="1.2" rot="R270" stop="yes" thermals="no"/>
<pad name="14" x="-7.015" y="-8.892" drill="0.7" diameter="1.2" rot="R270" stop="yes" thermals="no"/>
<pad name="15" x="-7.015" y="-11.432" drill="0.7" diameter="1.2" rot="R270" stop="yes" thermals="no"/>
<pad name="16" x="-7.015" y="-13.972" drill="0.7" diameter="1.2" rot="R270" stop="yes" thermals="no"/>
<pad name="17" x="-7.015" y="-16.512" drill="0.7" diameter="1.2" rot="R270" stop="yes" thermals="no"/>
<pad name="18" x="-7.015" y="-19.052" drill="0.7" diameter="1.2" rot="R270" stop="yes" thermals="no"/>
<pad name="19" x="-7.015" y="-21.592" drill="0.7" diameter="1.2" rot="R270" stop="yes" thermals="no"/>
<pad name="20" x="-7.015" y="-24.132" drill="0.7" diameter="1.2" rot="R270" stop="yes" thermals="no"/>
<pad name="40" x="7.985" y="24.128" drill="0.7" diameter="1.2" rot="R270" stop="yes" thermals="no"/>
<pad name="39" x="7.985" y="21.588" drill="0.7" diameter="1.2" rot="R270" stop="yes" thermals="no"/>
<pad name="38" x="7.985" y="19.048" drill="0.7" diameter="1.2" rot="R270" stop="yes" thermals="no"/>
<pad name="37" x="7.985" y="16.508" drill="0.7" diameter="1.2" rot="R270" stop="yes" thermals="no"/>
<pad name="36" x="7.985" y="13.968" drill="0.7" diameter="1.2" rot="R270" stop="yes" thermals="no"/>
<pad name="35" x="7.985" y="11.428" drill="0.7" diameter="1.2" rot="R270" stop="yes" thermals="no"/>
<pad name="34" x="7.985" y="8.888" drill="0.7" diameter="1.2" rot="R270" stop="yes" thermals="no"/>
<pad name="33" x="7.985" y="6.348" drill="0.7" diameter="1.2" rot="R270" stop="yes" thermals="no"/>
<pad name="32" x="7.985" y="3.808" drill="0.7" diameter="1.2" rot="R270" stop="yes" thermals="no"/>
<pad name="31" x="7.985" y="1.268" drill="0.7" diameter="1.2" rot="R270" stop="yes" thermals="no"/>
<pad name="30" x="7.985" y="-1.272" drill="0.7" diameter="1.2" rot="R270" stop="yes" thermals="no"/>
<pad name="29" x="7.985" y="-3.812" drill="0.7" diameter="1.2" rot="R270" stop="yes" thermals="no"/>
<pad name="28" x="7.985" y="-6.352" drill="0.7" diameter="1.2" rot="R270" stop="yes" thermals="no"/>
<pad name="27" x="7.985" y="-8.892" drill="0.7" diameter="1.2" rot="R270" stop="yes" thermals="no"/>
<pad name="26" x="7.985" y="-11.432" drill="0.7" diameter="1.2" rot="R270" stop="yes" thermals="no"/>
<pad name="25" x="7.985" y="-13.972" drill="0.7" diameter="1.2" rot="R270" stop="yes" thermals="no"/>
<pad name="24" x="7.985" y="-16.512" drill="0.7" diameter="1.2" rot="R270" stop="yes" thermals="no"/>
<pad name="23" x="7.985" y="-19.052" drill="0.7" diameter="1.2" rot="R270" stop="yes" thermals="no"/>
<pad name="22" x="7.985" y="-21.592" drill="0.7" diameter="1.2" rot="R270" stop="yes" thermals="no"/>
<pad name="21" x="7.985" y="-24.132" drill="0.7" diameter="1.2" rot="R270" stop="yes" thermals="no"/>
<wire layer="21" width="0.12" x1="-8.345" y1="25.828" x2="-5.685" y2="25.828"/>
<wire layer="21" width="0.12" x1="-5.685" y1="25.828" x2="-5.685" y2="-25.832"/>
<wire layer="21" width="0.12" x1="-5.685" y1="-25.832" x2="-8.345" y2="-25.832"/>
<wire layer="21" width="0.12" x1="-8.345" y1="-25.832" x2="-8.345" y2="25.828"/>
<circle layer="21" x="-7.005" y="26.986" radius="0.246" width="0"/>
<wire layer="51" width="0.12" x1="-8.345" y1="-25.832" x2="-8.345" y2="25.833"/>
<wire layer="51" width="0.12" x1="-8.345" y1="25.833" x2="-5.685" y2="25.833"/>
<wire layer="51" width="0.12" x1="-5.685" y1="25.833" x2="-5.685" y2="-25.827"/>
<wire layer="51" width="0.12" x1="-5.685" y1="-25.827" x2="-8.345" y2="-25.832"/>
<wire layer="51" width="0.12" x1="-8.345" y1="-25.832" x2="-8.345" y2="-25.832"/>
<wire layer="21" width="0.12" x1="6.655" y1="25.828" x2="9.315" y2="25.828"/>
<wire layer="21" width="0.12" x1="9.315" y1="25.828" x2="9.315" y2="-25.832"/>
<wire layer="21" width="0.12" x1="9.315" y1="-25.832" x2="6.655" y2="-25.832"/>
<wire layer="21" width="0.12" x1="6.655" y1="-25.832" x2="6.655" y2="25.828"/>
<wire layer="51" width="0.12" x1="6.655" y1="-25.832" x2="6.655" y2="25.833"/>
<wire layer="51" width="0.12" x1="6.655" y1="25.833" x2="9.315" y2="25.833"/>
<wire layer="51" width="0.12" x1="9.315" y1="25.833" x2="9.315" y2="-25.827"/>
<wire layer="51" width="0.12" x1="9.315" y1="-25.827" x2="6.655" y2="-25.832"/>
<wire layer="51" width="0.12" x1="6.655" y1="-25.832" x2="6.655" y2="-25.832"/>
</package>
<package name="SOP64P600X175-28N">
<smd name="1" x="-4.16" y="-2.712" layer="1" dx="0.3" dy="1.525" rot="R0" stop="yes" cream="yes" thermals="no"/>
<smd name="2" x="-3.52" y="-2.712" layer="1" dx="0.3" dy="1.525" rot="R0" stop="yes" cream="yes" thermals="no"/>
<smd name="3" x="-2.88" y="-2.712" layer="1" dx="0.3" dy="1.525" rot="R0" stop="yes" cream="yes" thermals="no"/>
<smd name="4" x="-2.24" y="-2.712" layer="1" dx="0.3" dy="1.525" rot="R0" stop="yes" cream="yes" thermals="no"/>
<smd name="5" x="-1.6" y="-2.712" layer="1" dx="0.3" dy="1.525" rot="R0" stop="yes" cream="yes" thermals="no"/>
<smd name="6" x="-0.96" y="-2.712" layer="1" dx="0.3" dy="1.525" rot="R0" stop="yes" cream="yes" thermals="no"/>
<smd name="7" x="-0.32" y="-2.712" layer="1" dx="0.3" dy="1.525" rot="R0" stop="yes" cream="yes" thermals="no"/>
<smd name="8" x="0.32" y="-2.712" layer="1" dx="0.3" dy="1.525" rot="R0" stop="yes" cream="yes" thermals="no"/>
<smd name="9" x="0.96" y="-2.712" layer="1" dx="0.3" dy="1.525" rot="R0" stop="yes" cream="yes" thermals="no"/>
<smd name="10" x="1.6" y="-2.712" layer="1" dx="0.3" dy="1.525" rot="R0" stop="yes" cream="yes" thermals="no"/>
<smd name="11" x="2.24" y="-2.712" layer="1" dx="0.3" dy="1.525" rot="R0" stop="yes" cream="yes" thermals="no"/>
<smd name="12" x="2.88" y="-2.712" layer="1" dx="0.3" dy="1.525" rot="R0" stop="yes" cream="yes" thermals="no"/>
<smd name="13" x="3.52" y="-2.712" layer="1" dx="0.3" dy="1.525" rot="R0" stop="yes" cream="yes" thermals="no"/>
<smd name="14" x="4.16" y="-2.712" layer="1" dx="0.3" dy="1.525" rot="R0" stop="yes" cream="yes" thermals="no"/>
<smd name="28" x="-4.16" y="2.712" layer="1" dx="0.3" dy="1.525" rot="R0" stop="yes" cream="yes" thermals="no"/>
<smd name="27" x="-3.52" y="2.712" layer="1" dx="0.3" dy="1.525" rot="R0" stop="yes" cream="yes" thermals="no"/>
<smd name="26" x="-2.88" y="2.712" layer="1" dx="0.3" dy="1.525" rot="R0" stop="yes" cream="yes" thermals="no"/>
<smd name="25" x="-2.24" y="2.712" layer="1" dx="0.3" dy="1.525" rot="R0" stop="yes" cream="yes" thermals="no"/>
<smd name="24" x="-1.6" y="2.712" layer="1" dx="0.3" dy="1.525" rot="R0" stop="yes" cream="yes" thermals="no"/>
<smd name="23" x="-0.96" y="2.712" layer="1" dx="0.3" dy="1.525" rot="R0" stop="yes" cream="yes" thermals="no"/>
<smd name="22" x="-0.32" y="2.712" layer="1" dx="0.3" dy="1.525" rot="R0" stop="yes" cream="yes" thermals="no"/>
<smd name="21" x="0.32" y="2.712" layer="1" dx="0.3" dy="1.525" rot="R0" stop="yes" cream="yes" thermals="no"/>
<smd name="20" x="0.96" y="2.712" layer="1" dx="0.3" dy="1.525" rot="R0" stop="yes" cream="yes" thermals="no"/>
<smd name="19" x="1.6" y="2.712" layer="1" dx="0.3" dy="1.525" rot="R0" stop="yes" cream="yes" thermals="no"/>
<smd name="18" x="2.24" y="2.712" layer="1" dx="0.3" dy="1.525" rot="R0" stop="yes" cream="yes" thermals="no"/>
<smd name="17" x="2.88" y="2.712" layer="1" dx="0.3" dy="1.525" rot="R0" stop="yes" cream="yes" thermals="no"/>
<smd name="16" x="3.52" y="2.712" layer="1" dx="0.3" dy="1.525" rot="R0" stop="yes" cream="yes" thermals="no"/>
<smd name="15" x="4.16" y="2.712" layer="1" dx="0.3" dy="1.525" rot="R0" stop="yes" cream="yes" thermals="no"/>
<wire layer="51" width="0.1" x1="-4.95" y1="-1.95" x2="-4.95" y2="1.95"/>
<wire layer="51" width="0.1" x1="-4.95" y1="1.95" x2="4.95" y2="1.95"/>
<wire layer="51" width="0.1" x1="4.95" y1="1.95" x2="4.95" y2="-1.95"/>
<wire layer="51" width="0.1" x1="4.95" y1="-1.95" x2="-4.95" y2="-1.95"/>
<wire layer="51" width="0.1" x1="-4.31" y1="-1.95" x2="-4.95" y2="-1.31"/>
<wire layer="21" width="0.2" x1="4.95" y1="-1.6" x2="-4.45" y2="-1.6"/>
<wire layer="21" width="0.2" x1="-4.45" y1="-1.6" x2="-4.95" y2="-1.1"/>
<wire layer="21" width="0.2" x1="-4.95" y1="-1.1" x2="-4.95" y2="1.6"/>
<wire layer="21" width="0.2" x1="-4.95" y1="1.6" x2="4.95" y2="1.6"/>
<wire layer="21" width="0.2" x1="4.95" y1="1.6" x2="4.95" y2="-1.6"/>
<circle layer="21" x="-5" y="-2" radius="0.4" width="0.4"/>
</package>
<package name="Q_1">
<pad name="1" x="-2.44" y="0" drill="0.8" diameter="1.6" rot="R0" stop="yes" thermals="no"/>
<pad name="2" x="2.44" y="0" drill="0.8" diameter="1.6" rot="R180" stop="yes" thermals="no"/>
<wire layer="21" width="0.12" x1="-3.35" y1="2.33" x2="3.35" y2="2.33"/>
<wire layer="21" width="0.12" x1="-3.35" y1="-2.33" x2="3.35" y2="-2.33"/>
<wire layer="21" width="0.12" x1="-3.35" y1="2.33" x2="-3.35" y2="-2.33" curve="180"/>
<wire layer="21" width="0.12" x1="3.35" y1="-2.33" x2="3.35" y2="2.33" curve="180"/>
<wire layer="51" width="0.12" x1="-3.35" y1="2.33" x2="3.35" y2="2.33"/>
<wire layer="51" width="0.12" x1="-3.35" y1="-2.33" x2="3.35" y2="-2.33"/>
<wire layer="51" width="0.12" x1="-3.35" y1="2.33" x2="-3.35" y2="-2.33" curve="180"/>
<wire layer="51" width="0.12" x1="3.35" y1="-2.33" x2="3.35" y2="2.33" curve="180"/>
</package>
<package name="DB25M">
<description>Unique Name: TE_DB25M</description>
<pad name="14" x="-15.24" y="-1.422" drill="0.8" diameter="1.5" rot="R0" stop="yes" thermals="no"/>
<pad name="15" x="-12.471" y="-1.422" drill="0.8" diameter="1.5" rot="R0" stop="yes" thermals="no"/>
<pad name="16" x="-9.703" y="-1.422" drill="0.8" diameter="1.5" rot="R0" stop="yes" thermals="no"/>
<pad name="17" x="-6.934" y="-1.422" drill="0.8" diameter="1.5" rot="R0" stop="yes" thermals="no"/>
<pad name="18" x="-4.166" y="-1.422" drill="0.8" diameter="1.5" rot="R0" stop="yes" thermals="no"/>
<pad name="19" x="-1.397" y="-1.422" drill="0.8" diameter="1.5" rot="R0" stop="yes" thermals="no"/>
<pad name="20" x="1.372" y="-1.422" drill="0.8" diameter="1.5" rot="R0" stop="yes" thermals="no"/>
<pad name="21" x="4.14" y="-1.422" drill="0.8" diameter="1.5" rot="R0" stop="yes" thermals="no"/>
<pad name="22" x="6.909" y="-1.422" drill="0.8" diameter="1.5" rot="R0" stop="yes" thermals="no"/>
<pad name="23" x="9.677" y="-1.422" drill="0.8" diameter="1.5" rot="R0" stop="yes" thermals="no"/>
<pad name="24" x="12.446" y="-1.422" drill="0.8" diameter="1.5" rot="R0" stop="yes" thermals="no"/>
<pad name="25" x="15.215" y="-1.422" drill="0.8" diameter="1.5" rot="R0" stop="yes" thermals="no"/>
<pad name="13" x="16.612" y="1.422" drill="0.8" diameter="1.5" rot="R0" stop="yes" thermals="no"/>
<pad name="12" x="13.843" y="1.422" drill="0.8" diameter="1.5" rot="R0" stop="yes" thermals="no"/>
<pad name="11" x="11.074" y="1.422" drill="0.8" diameter="1.5" rot="R0" stop="yes" thermals="no"/>
<pad name="1" x="-16.612" y="1.422" drill="0.8" diameter="1.5" rot="R0" stop="yes" thermals="no"/>
<pad name="2" x="-13.843" y="1.422" drill="0.8" diameter="1.5" rot="R0" stop="yes" thermals="no"/>
<pad name="3" x="-11.074" y="1.422" drill="0.8" diameter="1.5" rot="R0" stop="yes" thermals="no"/>
<pad name="4" x="-8.306" y="1.422" drill="0.8" diameter="1.5" rot="R0" stop="yes" thermals="no"/>
<pad name="5" x="-5.537" y="1.422" drill="0.8" diameter="1.5" rot="R0" stop="yes" thermals="no"/>
<pad name="6" x="-2.769" y="1.422" drill="0.8" diameter="1.5" rot="R0" stop="yes" thermals="no"/>
<pad name="7" x="0" y="1.422" drill="0.8" diameter="1.5" rot="R0" stop="yes" thermals="no"/>
<pad name="8" x="2.769" y="1.422" drill="0.8" diameter="1.5" rot="R0" stop="yes" thermals="no"/>
<pad name="9" x="5.537" y="1.422" drill="0.8" diameter="1.5" rot="R0" stop="yes" thermals="no"/>
<pad name="10" x="8.306" y="1.422" drill="0.8" diameter="1.5" rot="R0" stop="yes" thermals="no"/>
<pad name="@26_1" x="-23.5" y="0" drill="3.15" diameter="5" rot="R0" stop="yes" thermals="no"/>
<pad name="@26" x="23.5" y="0" drill="3.15" diameter="5" rot="R0" stop="yes" thermals="no"/>
<wire layer="21" width="0.25" x1="-26.721" y1="-6.477" x2="-26.721" y2="3.302"/>
<wire layer="21" width="0.25" x1="-26.721" y1="3.302" x2="26.721" y2="3.302"/>
<wire layer="21" width="0.25" x1="-26.721" y1="-6.477" x2="26.721" y2="-6.477"/>
<wire layer="21" width="0.25" x1="26.721" y1="-6.477" x2="26.721" y2="3.302"/>
</package>
<package name="FPC_24_1MM">
<pad name="15" x="-1" y="-2" drill="0.7" diameter="1.2" rot="R0" stop="yes" thermals="no"/>
<pad name="17" x="-1" y="-4" drill="0.7" diameter="1.2" rot="R0" stop="yes" thermals="no"/>
<pad name="19" x="-1" y="-6" drill="0.7" diameter="1.2" rot="R0" stop="yes" thermals="no"/>
<pad name="13" x="-1" y="0" drill="0.7" diameter="1.2" rot="R0" stop="yes" thermals="no"/>
<pad name="11" x="-1" y="2" drill="0.7" diameter="1.2" rot="R0" stop="yes" thermals="no"/>
<pad name="5" x="-1" y="8" drill="0.7" diameter="1.2" rot="R0" stop="yes" thermals="no"/>
<pad name="7" x="-1" y="6" drill="0.7" diameter="1.2" rot="R0" stop="yes" thermals="no"/>
<pad name="9" x="-1" y="4" drill="0.7" diameter="1.2" rot="R0" stop="yes" thermals="no"/>
<pad name="3" x="-1" y="10" drill="0.7" diameter="1.2" rot="R0" stop="yes" thermals="no"/>
<pad name="1" x="-1" y="12" drill="0.7" diameter="1.2" rot="R0" stop="yes" thermals="no"/>
<pad name="21" x="-1" y="-8" drill="0.7" diameter="1.2" rot="R0" stop="yes" thermals="no"/>
<pad name="23" x="-1" y="-10" drill="0.7" diameter="1.2" rot="R0" stop="yes" thermals="no"/>
<pad name="16" x="1" y="-3" drill="0.7" diameter="1.2" rot="R0" stop="yes" thermals="no"/>
<pad name="18" x="1" y="-5" drill="0.7" diameter="1.2" rot="R0" stop="yes" thermals="no"/>
<pad name="20" x="1" y="-7" drill="0.7" diameter="1.2" rot="R0" stop="yes" thermals="no"/>
<pad name="14" x="1" y="-1" drill="0.7" diameter="1.2" rot="R0" stop="yes" thermals="no"/>
<pad name="12" x="1" y="1" drill="0.7" diameter="1.2" rot="R0" stop="yes" thermals="no"/>
<pad name="6" x="1" y="7" drill="0.7" diameter="1.2" rot="R0" stop="yes" thermals="no"/>
<pad name="8" x="1" y="5" drill="0.7" diameter="1.2" rot="R0" stop="yes" thermals="no"/>
<pad name="10" x="1" y="3" drill="0.7" diameter="1.2" rot="R0" stop="yes" thermals="no"/>
<pad name="4" x="1" y="9" drill="0.7" diameter="1.2" rot="R0" stop="yes" thermals="no"/>
<pad name="2" x="1" y="11" drill="0.7" diameter="1.2" rot="R0" stop="yes" thermals="no"/>
<pad name="22" x="1" y="-9" drill="0.7" diameter="1.2" rot="R0" stop="yes" thermals="no"/>
<pad name="24" x="1" y="-11" drill="0.7" diameter="1.2" rot="R0" stop="yes" thermals="no"/>
<wire layer="51" width="0.25" x1="2.25" y1="13.5" x2="-1.25" y2="13.5"/>
<wire layer="51" width="0.25" x1="-1.25" y1="13.5" x2="-2.25" y2="12.5"/>
<wire layer="51" width="0.25" x1="-2.25" y1="12.5" x2="-2.25" y2="-12.5"/>
<wire layer="51" width="0.25" x1="-2.25" y1="-12.5" x2="2.25" y2="-12.5"/>
<wire layer="51" width="0.25" x1="2.25" y1="-12.5" x2="2.25" y2="13.5"/>
<circle layer="21" x="-2" y="14" radius="0.25" width="0"/>
<wire layer="21" width="0.25" x1="-2.25" y1="13.5" x2="2.25" y2="13.5"/>
<wire layer="21" width="0.25" x1="2.25" y1="13.5" x2="2.25" y2="-12.5"/>
<wire layer="21" width="0.25" x1="2.25" y1="-12.5" x2="-2.25" y2="-12.5"/>
<wire layer="21" width="0.25" x1="-2.25" y1="-12.5" x2="-2.25" y2="13.5"/>
</package>
<package name="PLS_16">
<pad name="1" x="-19.05" y="0" drill="0.9" shape="square" diameter="2" rot="R0" stop="yes" thermals="no"/>
<pad name="2" x="-16.51" y="0" drill="0.9" diameter="2" rot="R0" stop="yes" thermals="no"/>
<pad name="3" x="-13.97" y="0" drill="0.9" diameter="2" rot="R0" stop="yes" thermals="no"/>
<pad name="4" x="-11.43" y="0" drill="0.9" diameter="2" rot="R0" stop="yes" thermals="no"/>
<pad name="5" x="-8.89" y="0" drill="0.9" diameter="2" rot="R0" stop="yes" thermals="no"/>
<pad name="6" x="-6.35" y="0" drill="0.9" diameter="2" rot="R0" stop="yes" thermals="no"/>
<pad name="7" x="-3.81" y="0" drill="0.9" diameter="2" rot="R0" stop="yes" thermals="no"/>
<pad name="8" x="-1.27" y="0" drill="0.9" diameter="2" rot="R0" stop="yes" thermals="no"/>
<pad name="9" x="1.27" y="0" drill="0.9" diameter="2" rot="R0" stop="yes" thermals="no"/>
<pad name="10" x="3.81" y="0" drill="0.9" diameter="2" rot="R0" stop="yes" thermals="no"/>
<pad name="11" x="6.35" y="0" drill="0.9" diameter="2" rot="R0" stop="yes" thermals="no"/>
<pad name="12" x="8.89" y="0" drill="0.9" diameter="2" rot="R0" stop="yes" thermals="no"/>
<pad name="13" x="11.43" y="0" drill="0.9" diameter="2" rot="R0" stop="yes" thermals="no"/>
<pad name="14" x="13.97" y="0" drill="0.9" diameter="2" rot="R0" stop="yes" thermals="no"/>
<pad name="15" x="16.51" y="0" drill="0.9" diameter="2" rot="R0" stop="yes" thermals="no"/>
<pad name="16" x="19.05" y="0" drill="0.9" diameter="2" rot="R0" stop="yes" thermals="no"/>
<wire layer="21" width="0.25" x1="20.32" y1="-1.27" x2="20.32" y2="1.27"/>
<wire layer="21" width="0.25" x1="-18.41" y1="1.27" x2="20.32" y2="1.27"/>
<wire layer="21" width="0.25" x1="-20.32" y1="1.27" x2="-18.41" y2="1.27"/>
<wire layer="21" width="0.25" x1="-20.32" y1="-1.27" x2="-20.32" y2="1.27"/>
<wire layer="21" width="0.25" x1="-20.32" y1="-1.27" x2="20.32" y2="-1.27"/>
</package>
<package name="J-1">
<pad name="1" x="7" y="0" drill="2.3" diameter="4" rot="R0" stop="yes" thermals="no"/>
<pad name="2" x="0" y="0" drill="2.3" diameter="4" rot="R0" stop="yes" thermals="no"/>
<pad name="3" x="4" y="-4.5" drill="2.3" diameter="4" rot="R270" stop="yes" thermals="no"/>
<wire layer="21" width="0.12" x1="-7" y1="-4.5" x2="7" y2="-4.5"/>
<wire layer="21" width="0.12" x1="7" y1="-4.5" x2="7" y2="4.5"/>
<wire layer="21" width="0.12" x1="7" y1="4.5" x2="-7" y2="4.5"/>
<wire layer="21" width="0.12" x1="-7" y1="4.5" x2="-7" y2="-4.5"/>
<wire layer="51" width="0.12" x1="-7" y1="4.5" x2="7" y2="4.5"/>
<wire layer="51" width="0.12" x1="7" y1="4.5" x2="7" y2="-4.5"/>
<wire layer="51" width="0.12" x1="7" y1="-4.5" x2="-7" y2="-4.5"/>
<wire layer="51" width="0.12" x1="-7" y1="-4.5" x2="-7" y2="4.5"/>
</package>
<package name="SOT95P280X145-6N">
<description>MF: Maxim Integrated Products
Description: 
                        
                            Low-Side Gate Driver IC Inverting, Non-Inverting SOT-23-6
                        
                    
Package: SOT-23-6 Maxim Integrated
Price: None
SnapEDA_Link: https://www.snapeda.com/parts/MAX15070AAUT+T/Maxim+Integrated/view-part/?ref=snap
MP: MAX15070AAUT+T
Availability: In Stock
Check_prices: https://www.snapeda.com/parts/MAX15070AAUT+T/Maxim+Integrated/view-part/?ref=eda</description>
<smd name="1" x="-1.245" y="0.95" layer="1" dx="1.22" dy="0.6" roundness="50" rot="R0" stop="yes" cream="yes" thermals="no"/>
<smd name="3" x="-1.245" y="-0.95" layer="1" dx="1.22" dy="0.6" roundness="50" rot="R0" stop="yes" cream="yes" thermals="no"/>
<smd name="6" x="1.245" y="0.95" layer="1" dx="1.22" dy="0.6" roundness="50" rot="R0" stop="yes" cream="yes" thermals="no"/>
<smd name="4" x="1.245" y="-0.95" layer="1" dx="1.22" dy="0.6" roundness="50" rot="R0" stop="yes" cream="yes" thermals="no"/>
<smd name="5" x="1.245" y="0" layer="1" dx="1.22" dy="0.6" roundness="50" rot="R0" stop="yes" cream="yes" thermals="no"/>
<smd name="2" x="-1.245" y="0" layer="1" dx="1.22" dy="0.6" roundness="50" rot="R0" stop="yes" cream="yes" thermals="no"/>
<wire layer="51" width="0.127" x1="-0.88" y1="-1.5" x2="-0.88" y2="1.5"/>
<wire layer="51" width="0.127" x1="-0.88" y1="1.5" x2="0.88" y2="1.5"/>
<wire layer="51" width="0.127" x1="0.88" y1="1.5" x2="0.88" y2="-1.5"/>
<wire layer="51" width="0.127" x1="0.88" y1="-1.5" x2="-0.88" y2="-1.5"/>
<wire layer="21" width="0.127" x1="-0.88" y1="1.57" x2="0.88" y2="1.57"/>
<wire layer="21" width="0.127" x1="-0.88" y1="-1.57" x2="0.88" y2="-1.57"/>
<circle layer="21" x="-2.5" y="1" radius="0.2" width="0"/>
<circle layer="51" x="-2.5" y="1" radius="0.2" width="0"/>
</package>
<package name="TO127P1500X440-8N">
<description>MF: Infineon Technologies
Description: 
                        
                            Half Bridge Driver DC Motors, General Purpose Power MOSFET PG-TO263-7-1
                        
                    
Package: TO-263-8 Infineon Technologies
Price: None
SnapEDA_Link: https://www.snapeda.com/parts/IFX007T/Infineon/view-part/?ref=snap
MP: IFX007T
Availability: Not in stock
Check_prices: https://www.snapeda.com/parts/IFX007T/Infineon/view-part/?ref=eda</description>
<smd name="1" x="-6.07" y="3.81" layer="1" dx="3.67" dy="0.79" roundness="26" rot="R0" stop="yes" cream="yes" thermals="no"/>
<smd name="4" x="-6.07" y="0" layer="1" dx="3.67" dy="0.79" roundness="26" rot="R0" stop="yes" cream="yes" thermals="no"/>
<smd name="2" x="-6.07" y="2.54" layer="1" dx="3.67" dy="0.79" roundness="26" rot="R0" stop="yes" cream="yes" thermals="no"/>
<smd name="3" x="-6.07" y="1.27" layer="1" dx="3.67" dy="0.79" roundness="26" rot="R0" stop="yes" cream="yes" thermals="no"/>
<smd name="5" x="-6.07" y="-1.27" layer="1" dx="3.67" dy="0.79" roundness="26" rot="R0" stop="yes" cream="yes" thermals="no"/>
<smd name="6" x="-6.07" y="-2.54" layer="1" dx="3.67" dy="0.79" roundness="26" rot="R0" stop="yes" cream="yes" thermals="no"/>
<smd name="7" x="-6.07" y="-3.81" layer="1" dx="3.67" dy="0.79" roundness="26" rot="R0" stop="yes" cream="yes" thermals="no"/>
<smd name="8" x="3.89" y="0" layer="1" dx="8.04" dy="8.67" rot="R0" stop="yes" cream="no" thermals="no"/>
<wire layer="51" width="0.127" x1="6.67" y1="5" x2="6.67" y2="-5"/>
<wire layer="51" width="0.127" x1="6.67" y1="-5" x2="-2.59" y2="-5"/>
<wire layer="51" width="0.127" x1="-2.59" y1="-5" x2="-2.59" y2="5"/>
<wire layer="51" width="0.127" x1="-2.59" y1="5" x2="6.67" y2="5"/>
<wire layer="21" width="0.127" x1="6.67" y1="5" x2="-2.59" y2="5"/>
<wire layer="21" width="0.127" x1="-2.59" y1="5" x2="-2.59" y2="-5"/>
<wire layer="21" width="0.127" x1="-2.59" y1="-5" x2="6.67" y2="-5"/>
<circle layer="21" x="-8.5" y="3.81" radius="0.2" width="0"/>
<circle layer="51" x="-8.5" y="3.81" radius="0.2" width="0"/>
<rectangle x1="3.06" y1="1.785" x2="4.72" y2="0.385" layer="31" rot="R0"/>
<rectangle x1="3.06" y1="-0.385" x2="4.72" y2="-1.785" layer="31" rot="R0"/>
<rectangle x1="3.06" y1="3.955" x2="4.72" y2="2.555" layer="31" rot="R0"/>
<rectangle x1="3.06" y1="-2.555" x2="4.72" y2="-3.955" layer="31" rot="R0"/>
<rectangle x1="0.38" y1="1.785" x2="2.04" y2="0.385" layer="31" rot="R0"/>
<rectangle x1="0.38" y1="-0.385" x2="2.04" y2="-1.785" layer="31" rot="R0"/>
<rectangle x1="0.38" y1="3.955" x2="2.04" y2="2.555" layer="31" rot="R0"/>
<rectangle x1="0.38" y1="-2.555" x2="2.04" y2="-3.955" layer="31" rot="R0"/>
<rectangle x1="5.74" y1="1.785" x2="7.4" y2="0.385" layer="31" rot="R0"/>
<rectangle x1="5.74" y1="-0.385" x2="7.4" y2="-1.785" layer="31" rot="R0"/>
<rectangle x1="5.74" y1="3.955" x2="7.4" y2="2.555" layer="31" rot="R0"/>
<rectangle x1="5.74" y1="-2.555" x2="7.4" y2="-3.955" layer="31" rot="R0"/>
</package>
<package name="PLS_5">
<description>LINK: &lt;a href="http://vinratel.at.ua/"&gt;http://vinratel.at.ua/&lt;/a&gt;
author: &lt;a href="&#1044;&#1072;&#1085;&#1100;&#1082;&#1086;&#1074;&#1089;&#1082;&#1080;&#1081; &#1042;.&#1048;."&gt;&#1044;&#1072;&#1085;&#1100;&#1082;&#1086;&#1074;&#1089;&#1082;&#1080;&#1081; &#1042;.&#1048;.&lt;/a&gt;
mail: dvi534538@mail/ru</description>
<pad name="1" x="-5.08" y="0" drill="0.9" shape="square" diameter="2" rot="R0" stop="yes" thermals="no"/>
<pad name="2" x="-2.54" y="0" drill="0.9" diameter="2" rot="R0" stop="yes" thermals="no"/>
<pad name="3" x="0" y="0" drill="0.9" diameter="2" rot="R0" stop="yes" thermals="no"/>
<pad name="4" x="2.54" y="0" drill="0.9" diameter="2" rot="R0" stop="yes" thermals="no"/>
<pad name="5" x="5.08" y="0" drill="0.9" diameter="2" rot="R0" stop="yes" thermals="no"/>
<wire layer="21" width="0.25" x1="6.35" y1="-1.27" x2="6.35" y2="1.27"/>
<wire layer="21" width="0.25" x1="-6.35" y1="-1.27" x2="6.35" y2="-1.27"/>
<wire layer="21" width="0.25" x1="-6.35" y1="1.27" x2="6.35" y2="1.27"/>
<wire layer="21" width="0.25" x1="-6.35" y1="-1.27" x2="-6.35" y2="1.27"/>
</package>
<package name="СAP_0805_1206">
<smd name="1@_1" x="-0.9" y="0" layer="1" dx="1.21" dy="1.57" roundness="41" rot="R0" stop="yes" cream="yes" thermals="no"/>
<smd name="2@_1" x="0.9" y="0" layer="1" dx="1.21" dy="1.57" roundness="41" rot="R180" stop="yes" cream="yes" thermals="no"/>
<smd name="1@" x="-1.525" y="0" layer="1" dx="1.26" dy="1.92" roundness="40" rot="R0" stop="yes" cream="yes" thermals="no"/>
<smd name="2@" x="1.525" y="0" layer="1" dx="1.26" dy="1.92" roundness="40" rot="R180" stop="yes" cream="yes" thermals="no"/>
<wire layer="51" width="0.12" x1="-2.5" y1="1.27" x2="2.5" y2="1.27"/>
<wire layer="51" width="0.12" x1="2.5" y1="1.27" x2="2.5" y2="-1.27"/>
<wire layer="51" width="0.12" x1="2.5" y1="-1.27" x2="-2.5" y2="-1.27"/>
<wire layer="51" width="0.12" x1="-2.5" y1="-1.27" x2="-2.5" y2="1.27"/>
<wire layer="21" width="0.15" x1="-0.67" y1="1.059" x2="0.67" y2="1.059"/>
<wire layer="21" width="0.15" x1="-0.67" y1="-1.005" x2="0.67" y2="-1.005"/>
</package>
</packages>
<symbols>
<symbol name="USB-1_TYPE_B">
<wire layer="94" width="0.25" x1="-6.35" y1="7.62" x2="6.35" y2="7.62"/>
<wire layer="94" width="0.25" x1="6.35" y1="7.62" x2="6.35" y2="-7.62"/>
<wire layer="94" width="0.25" x1="6.35" y1="-7.62" x2="-6.35" y2="-7.62"/>
<wire layer="94" width="0.25" x1="-6.35" y1="-7.62" x2="-6.35" y2="7.62"/>
<pin name="VBUS" visible="both" length="short" direction="pwr" rot="R180" x="8.89" y="5.08"/>
<pin name="D-" visible="both" length="short" direction="io" x="-8.89" y="-2.54"/>
<pin name="D+" visible="both" length="short" direction="io" x="-8.89" y="2.54"/>
<pin name="CASE" visible="both" length="short" direction="pwr" rot="R180" x="8.89" y="-5.08"/>
<pin name="GND" visible="both" length="short" direction="pwr" rot="R180" x="8.89" y="0"/>
</symbol>
<symbol name="+5V">
<wire layer="94" width="0.25" x1="-2.54" y1="0" x2="2.54" y2="0"/>
<pin name="+5V" visible="pad" length="short" direction="sup" rot="R90" x="0" y="-2.54"/>
</symbol>
<symbol name="R_0805_1206">
<wire layer="94" width="0.25" x1="3.175" y1="-1.27" x2="3.81" y2="0"/>
<wire layer="94" width="0.25" x1="1.905" y1="1.27" x2="3.175" y2="-1.27"/>
<wire layer="94" width="0.25" x1="0.635" y1="-1.27" x2="1.905" y2="1.27"/>
<wire layer="94" width="0.25" x1="-0.635" y1="1.27" x2="0.635" y2="-1.27"/>
<wire layer="94" width="0.25" x1="-1.905" y1="-1.27" x2="-0.635" y2="1.27"/>
<wire layer="94" width="0.25" x1="-3.175" y1="1.27" x2="-1.905" y2="-1.27"/>
<wire layer="94" width="0.25" x1="-3.81" y1="0" x2="-3.175" y2="1.27"/>
<pin name="2" visible="pad" length="short" direction="pas" rot="R180" x="6.35" y="0"/>
<pin name="1" visible="pad" length="short" direction="pas" x="-6.35" y="0"/>
</symbol>
<symbol name="PLS_2">
<wire layer="94" width="0.25" x1="-9.525" y1="2.54" x2="-9.525" y2="-2.54"/>
<wire layer="94" width="0.25" x1="-9.525" y1="-2.54" x2="-8.255" y2="-2.54"/>
<wire layer="94" width="0.25" x1="-6.985" y1="-2.54" x2="-8.255" y2="-2.54"/>
<wire layer="94" width="0.25" x1="-5.715" y1="-2.54" x2="-5.715" y2="2.54"/>
<wire layer="94" width="0.25" x1="-6.985" y1="2.54" x2="-9.525" y2="2.54"/>
<wire layer="94" width="0.25" x1="-9.525" y1="0" x2="-6.985" y2="0"/>
<wire layer="94" width="0.25" x1="-6.985" y1="2.54" x2="9.525" y2="2.54"/>
<wire layer="94" width="0.25" x1="-6.985" y1="0" x2="9.525" y2="0"/>
<wire layer="94" width="0.25" x1="-6.985" y1="-2.54" x2="9.525" y2="-2.54"/>
<wire layer="94" width="0.25" x1="9.525" y1="2.54" x2="9.525" y2="-2.54"/>
<pin name="1" visible="both" length="short" direction="nc" x="-12.065" y="1.27"/>
<pin name="2" visible="both" length="short" direction="nc" x="-12.065" y="-1.27"/>
</symbol>
<symbol name="USB-1_TYPE_A">
<wire layer="94" width="0.25" x1="-6.35" y1="7.62" x2="6.35" y2="7.62"/>
<wire layer="94" width="0.25" x1="6.35" y1="7.62" x2="6.35" y2="-7.62"/>
<wire layer="94" width="0.25" x1="6.35" y1="-7.62" x2="-6.35" y2="-7.62"/>
<wire layer="94" width="0.25" x1="-6.35" y1="-7.62" x2="-6.35" y2="7.62"/>
<pin name="VBUS" visible="both" length="short" direction="pwr" rot="R180" x="8.89" y="5.08"/>
<pin name="D-" visible="both" length="short" direction="io" x="-8.89" y="-2.54"/>
<pin name="D+" visible="both" length="short" direction="io" x="-8.89" y="2.54"/>
<pin name="CASE" visible="both" length="short" direction="pwr" rot="R180" x="8.89" y="-5.08"/>
<pin name="GND" visible="both" length="short" direction="pwr" rot="R180" x="8.89" y="0"/>
</symbol>
<symbol name="CAP_P_5MM">
<wire layer="94" width="0.254" x1="1.427" y1="1.911" x2="1.427" y2="-1.911" curve="74.02156"/>
<wire layer="94" width="0.25" x1="-0.788" y1="0" x2="0.152" y2="0"/>
<wire layer="94" width="0.25" x1="0.787" y1="0" x2="1.753" y2="0"/>
<wire layer="94" width="0.25" x1="0.152" y1="-1.905" x2="0.152" y2="1.905"/>
<wire layer="94" width="0.25" x1="-1.118" y1="0.635" x2="-1.118" y2="1.905"/>
<wire layer="94" width="0.25" x1="-1.753" y1="1.27" x2="-0.483" y2="1.27"/>
<pin name="PLUS" visible="pad" length="short" direction="pas" x="-3.327" y="0"/>
<pin name="MINUS" visible="pad" length="short" direction="pas" rot="R180" x="4.293" y="0"/>
</symbol>
<symbol name="CAP_P_3MM">
<wire layer="94" width="0.254" x1="1.427" y1="1.911" x2="1.427" y2="-1.911" curve="74.02156"/>
<wire layer="94" width="0.25" x1="-0.788" y1="0" x2="0.152" y2="0"/>
<wire layer="94" width="0.25" x1="0.787" y1="0" x2="1.753" y2="0"/>
<wire layer="94" width="0.25" x1="0.152" y1="-1.905" x2="0.152" y2="1.905"/>
<wire layer="94" width="0.25" x1="-1.118" y1="0.635" x2="-1.118" y2="1.905"/>
<wire layer="94" width="0.25" x1="-1.753" y1="1.27" x2="-0.483" y2="1.27"/>
<pin name="PLUS" visible="pad" length="short" direction="pas" x="-3.327" y="0"/>
<pin name="MINUS" visible="pad" length="short" direction="pas" rot="R180" x="4.293" y="0"/>
</symbol>
<symbol name="2_SCREW_TERM._BLK.">
<wire layer="94" width="0.25" x1="-2.54" y1="3.81" x2="2.54" y2="3.81"/>
<wire layer="94" width="0.25" x1="2.54" y1="3.81" x2="2.54" y2="-3.81"/>
<wire layer="94" width="0.25" x1="2.54" y1="-3.81" x2="-2.54" y2="-3.81"/>
<wire layer="94" width="0.25" x1="-2.54" y1="-3.81" x2="-2.54" y2="3.81"/>
<pin name="2" visible="pad" length="short" direction="nc" x="-5.08" y="2.54"/>
<pin name="1" visible="pad" length="short" direction="nc" x="-5.08" y="-2.54"/>
</symbol>
<symbol name="PLS_3">
<wire layer="94" width="0.25" x1="-5.715" y1="3.81" x2="-5.715" y2="-3.81"/>
<wire layer="94" width="0.25" x1="-5.715" y1="-3.81" x2="-3.175" y2="-3.81"/>
<wire layer="94" width="0.25" x1="-1.905" y1="3.81" x2="-1.905" y2="-3.81"/>
<wire layer="94" width="0.25" x1="-5.715" y1="3.81" x2="-3.175" y2="3.81"/>
<wire layer="94" width="0.25" x1="-5.715" y1="1.27" x2="-3.175" y2="1.27"/>
<wire layer="94" width="0.25" x1="-5.715" y1="-1.27" x2="-3.175" y2="-1.27"/>
<wire layer="94" width="0.25" x1="-3.175" y1="3.81" x2="13.335" y2="3.81"/>
<wire layer="94" width="0.25" x1="-3.175" y1="1.27" x2="13.335" y2="1.27"/>
<wire layer="94" width="0.25" x1="-3.175" y1="-1.27" x2="13.335" y2="-1.27"/>
<wire layer="94" width="0.25" x1="-3.175" y1="-3.81" x2="13.335" y2="-3.81"/>
<wire layer="94" width="0.25" x1="13.335" y1="3.81" x2="13.335" y2="-3.81"/>
<pin name="1" visible="both" length="short" direction="nc" x="-8.255" y="2.54"/>
<pin name="2" visible="both" length="short" direction="nc" x="-8.255" y="0"/>
<pin name="3" visible="both" length="short" direction="nc" x="-8.255" y="-2.54"/>
</symbol>
<symbol name="CAP_SMD_P_5MM">
<wire layer="94" width="0.254" x1="1.427" y1="1.911" x2="1.427" y2="-1.911" curve="74.02156"/>
<wire layer="94" width="0.25" x1="-0.788" y1="0" x2="0.152" y2="0"/>
<wire layer="94" width="0.25" x1="0.787" y1="0" x2="1.753" y2="0"/>
<wire layer="94" width="0.25" x1="0.152" y1="-1.905" x2="0.152" y2="1.905"/>
<wire layer="94" width="0.25" x1="-1.118" y1="0.635" x2="-1.118" y2="1.905"/>
<wire layer="94" width="0.25" x1="-1.753" y1="1.27" x2="-0.483" y2="1.27"/>
<pin name="PLUS" visible="pad" length="short" direction="pas" x="-3.327" y="0"/>
<pin name="MINUS" visible="pad" length="short" direction="pas" rot="R180" x="4.293" y="0"/>
</symbol>
<symbol name="GND">
<wire layer="94" width="0.25" x1="-1.905" y1="1.016" x2="1.905" y2="1.016"/>
<wire layer="94" width="0.25" x1="-1.27" y1="0" x2="1.27" y2="0"/>
<wire layer="94" width="0.25" x1="-0.508" y1="-1.016" x2="0.508" y2="-1.016"/>
<pin name="GND" visible="pad" length="short" direction="sup" rot="R270" x="0" y="3.556"/>
</symbol>
<symbol name="BLUE_PILL_STM32F103">
<wire layer="94" width="0.25" x1="-20.342" y1="25.392" x2="-14.95" y2="25.392"/>
<wire layer="94" width="0.25" x1="-14.95" y1="25.392" x2="-14.95" y2="-25.424"/>
<wire layer="94" width="0.25" x1="-14.95" y1="-25.424" x2="-20.342" y2="-25.424"/>
<wire layer="94" width="0.25" x1="-20.342" y1="-25.424" x2="-20.342" y2="25.392"/>
<wire layer="94" width="0.25" x1="-14.95" y1="25.392" x2="-0.022" y2="25.392"/>
<wire layer="94" width="0.25" x1="-0.022" y1="25.392" x2="-0.022" y2="-25.424"/>
<wire layer="94" width="0.25" x1="-0.022" y1="-25.424" x2="-14.95" y2="-25.424"/>
<wire layer="94" width="0.25" x1="-14.95" y1="-25.424" x2="-14.95" y2="25.392"/>
<wire layer="94" width="0.25" x1="-20.342" y1="22.836" x2="-0.022" y2="22.836"/>
<wire layer="94" width="0.25" x1="-20.342" y1="20.296" x2="-0.022" y2="20.296"/>
<wire layer="94" width="0.25" x1="-20.342" y1="17.756" x2="-0.022" y2="17.756"/>
<wire layer="94" width="0.25" x1="-20.342" y1="15.216" x2="-19.072" y2="15.216"/>
<wire layer="94" width="0.25" x1="-0.022" y1="15.216" x2="-19.072" y2="15.216"/>
<wire layer="94" width="0.25" x1="-20.342" y1="12.676" x2="-0.022" y2="12.676"/>
<wire layer="94" width="0.25" x1="-20.342" y1="10.136" x2="-0.022" y2="10.136"/>
<wire layer="94" width="0.25" x1="-20.342" y1="7.596" x2="-0.022" y2="7.596"/>
<wire layer="94" width="0.25" x1="-20.342" y1="5.056" x2="-0.022" y2="5.056"/>
<wire layer="94" width="0.25" x1="-20.342" y1="2.516" x2="-0.022" y2="2.516"/>
<wire layer="94" width="0.25" x1="-20.342" y1="-0.024" x2="-0.022" y2="-0.024"/>
<wire layer="94" width="0.25" x1="-20.342" y1="-2.564" x2="-0.022" y2="-2.564"/>
<wire layer="94" width="0.25" x1="-20.342" y1="-5.104" x2="-0.022" y2="-5.104"/>
<wire layer="94" width="0.25" x1="-20.342" y1="-7.644" x2="-0.022" y2="-7.644"/>
<wire layer="94" width="0.25" x1="-20.342" y1="-10.184" x2="-0.022" y2="-10.184"/>
<wire layer="94" width="0.25" x1="-20.342" y1="-12.724" x2="-0.022" y2="-12.724"/>
<wire layer="94" width="0.25" x1="-20.342" y1="-15.264" x2="-0.022" y2="-15.264"/>
<wire layer="94" width="0.25" x1="-20.342" y1="-17.804" x2="-0.022" y2="-17.804"/>
<wire layer="94" width="0.25" x1="-20.342" y1="-20.344" x2="-0.022" y2="-20.344"/>
<wire layer="94" width="0.25" x1="-20.342" y1="-22.884" x2="-0.022" y2="-22.884"/>
<wire layer="94" width="0.25" x1="14.91" y1="25.394" x2="20.302" y2="25.394"/>
<wire layer="94" width="0.25" x1="20.302" y1="25.394" x2="20.302" y2="-25.422"/>
<wire layer="94" width="0.25" x1="20.302" y1="-25.422" x2="14.91" y2="-25.422"/>
<wire layer="94" width="0.25" x1="14.91" y1="-25.422" x2="14.91" y2="25.394"/>
<wire layer="94" width="0.25" x1="-0.018" y1="25.394" x2="14.91" y2="25.394"/>
<wire layer="94" width="0.25" x1="14.91" y1="25.394" x2="14.91" y2="-25.422"/>
<wire layer="94" width="0.25" x1="14.91" y1="-25.422" x2="-0.018" y2="-25.422"/>
<wire layer="94" width="0.25" x1="-0.018" y1="-25.422" x2="-0.018" y2="25.394"/>
<wire layer="94" width="0.25" x1="20.302" y1="-22.866" x2="-0.018" y2="-22.866"/>
<wire layer="94" width="0.25" x1="20.302" y1="-20.326" x2="-0.018" y2="-20.326"/>
<wire layer="94" width="0.25" x1="20.302" y1="-17.786" x2="-0.018" y2="-17.786"/>
<wire layer="94" width="0.25" x1="20.302" y1="-15.246" x2="19.032" y2="-15.246"/>
<wire layer="94" width="0.25" x1="-0.018" y1="-15.246" x2="19.032" y2="-15.246"/>
<wire layer="94" width="0.25" x1="20.302" y1="-12.706" x2="-0.018" y2="-12.706"/>
<wire layer="94" width="0.25" x1="20.302" y1="-10.166" x2="-0.018" y2="-10.166"/>
<wire layer="94" width="0.25" x1="20.302" y1="-7.626" x2="-0.018" y2="-7.626"/>
<wire layer="94" width="0.25" x1="20.302" y1="-5.086" x2="-0.018" y2="-5.086"/>
<wire layer="94" width="0.25" x1="20.302" y1="-2.546" x2="-0.018" y2="-2.546"/>
<wire layer="94" width="0.25" x1="20.302" y1="-0.006" x2="-0.018" y2="-0.006"/>
<wire layer="94" width="0.25" x1="20.302" y1="2.534" x2="-0.018" y2="2.534"/>
<wire layer="94" width="0.25" x1="20.302" y1="5.074" x2="-0.018" y2="5.074"/>
<wire layer="94" width="0.25" x1="20.302" y1="7.614" x2="-0.018" y2="7.614"/>
<wire layer="94" width="0.25" x1="20.302" y1="10.154" x2="-0.018" y2="10.154"/>
<wire layer="94" width="0.25" x1="20.302" y1="12.694" x2="-0.018" y2="12.694"/>
<wire layer="94" width="0.25" x1="20.302" y1="15.234" x2="-0.018" y2="15.234"/>
<wire layer="94" width="0.25" x1="20.302" y1="17.774" x2="-0.018" y2="17.774"/>
<wire layer="94" width="0.25" x1="20.302" y1="20.314" x2="-0.018" y2="20.314"/>
<wire layer="94" width="0.25" x1="20.302" y1="22.854" x2="-0.018" y2="22.854"/>
<pin name="B12" visible="both" length="short" direction="nc" x="-22.882" y="24.106"/>
<pin name="B13" visible="both" length="short" direction="nc" x="-22.882" y="21.584"/>
<pin name="B14" visible="both" length="short" direction="nc" x="-22.882" y="19.026"/>
<pin name="B15" visible="both" length="short" direction="nc" x="-22.882" y="16.486"/>
<pin name="A8" visible="both" length="short" direction="nc" x="-22.882" y="13.964"/>
<pin name="A9" visible="both" length="short" direction="nc" x="-22.882" y="11.406"/>
<pin name="A10" visible="both" length="short" direction="nc" x="-22.882" y="8.866"/>
<pin name="A11" visible="both" length="short" direction="nc" x="-22.882" y="6.344"/>
<pin name="A12" visible="both" length="short" direction="nc" x="-22.882" y="3.786"/>
<pin name="A15" visible="both" length="short" direction="nc" x="-22.882" y="1.246"/>
<pin name="B3" visible="both" length="short" direction="nc" x="-22.882" y="-1.276"/>
<pin name="B4" visible="both" length="short" direction="nc" x="-22.882" y="-3.816"/>
<pin name="B5" visible="both" length="short" direction="nc" x="-22.882" y="-6.356"/>
<pin name="B6" visible="both" length="short" direction="nc" x="-22.882" y="-8.914"/>
<pin name="B7" visible="both" length="short" direction="nc" x="-22.882" y="-11.454"/>
<pin name="B8" visible="both" length="short" direction="nc" x="-22.882" y="-13.976"/>
<pin name="B9" visible="both" length="short" direction="nc" x="-22.882" y="-16.534"/>
<pin name="5v" visible="both" length="short" direction="nc" x="-22.882" y="-19.074"/>
<pin name="G@1" visible="both" length="short" direction="nc" x="-22.882" y="-21.614"/>
<pin name="3.3v@1" visible="both" length="short" direction="nc" x="-22.882" y="-24.136"/>
<pin name="BAT" visible="both" length="short" direction="nc" rot="R180" x="22.842" y="-24.136"/>
<pin name="C13" visible="both" length="short" direction="nc" rot="R180" x="22.842" y="-21.596"/>
<pin name="C14" visible="both" length="short" direction="nc" rot="R180" x="22.842" y="-19.056"/>
<pin name="C15" visible="both" length="short" direction="nc" rot="R180" x="22.842" y="-16.516"/>
<pin name="A0" visible="both" length="short" direction="nc" rot="R180" x="22.842" y="-13.976"/>
<pin name="A1" visible="both" length="short" direction="nc" rot="R180" x="22.842" y="-11.436"/>
<pin name="A2" visible="both" length="short" direction="nc" rot="R180" x="22.842" y="-8.896"/>
<pin name="A3" visible="both" length="short" direction="nc" rot="R180" x="22.842" y="-6.356"/>
<pin name="A4" visible="both" length="short" direction="nc" rot="R180" x="22.842" y="-3.816"/>
<pin name="A5" visible="both" length="short" direction="nc" rot="R180" x="22.842" y="-1.276"/>
<pin name="A6" visible="both" length="short" direction="nc" rot="R180" x="22.842" y="1.264"/>
<pin name="A7" visible="both" length="short" direction="nc" rot="R180" x="22.842" y="3.804"/>
<pin name="B0" visible="both" length="short" direction="nc" rot="R180" x="22.842" y="6.344"/>
<pin name="B1" visible="both" length="short" direction="nc" rot="R180" x="22.842" y="8.866"/>
<pin name="B10" visible="both" length="short" direction="nc" rot="R180" x="22.842" y="11.406"/>
<pin name="B11" visible="both" length="short" direction="nc" rot="R180" x="22.842" y="13.964"/>
<pin name="R" visible="both" length="short" direction="nc" rot="R180" x="22.842" y="16.486"/>
<pin name="3.3v@2" visible="both" length="short" direction="nc" rot="R180" x="22.842" y="19.044"/>
<pin name="G@2" visible="both" length="short" direction="nc" rot="R180" x="22.842" y="21.584"/>
<pin name="G@3" visible="both" length="short" direction="nc" rot="R180" x="22.842" y="24.106"/>
</symbol>
<symbol name="FE1.1S">
<wire layer="94" width="0.254" x1="-10.16" y1="30.48" x2="12.7" y2="30.48"/>
<wire layer="94" width="0.254" x1="12.7" y1="-35.56" x2="12.7" y2="0"/>
<wire layer="94" width="0.254" x1="12.7" y1="0" x2="12.7" y2="30.48"/>
<wire layer="94" width="0.254" x1="12.7" y1="-35.56" x2="-10.16" y2="-35.56"/>
<wire layer="94" width="0.254" x1="-10.16" y1="30.48" x2="-10.16" y2="0"/>
<wire layer="94" width="0.254" x1="-10.16" y1="0" x2="-10.16" y2="-35.56"/>
<wire layer="94" width="0.254" x1="-10.16" y1="0" x2="12.7" y2="0"/>
<pin name="VSS" visible="both" length="short" direction="io" x="-12.7" y="-33.02"/>
<pin name="XOUT" visible="both" length="short" direction="io" x="-12.7" y="-22.86"/>
<pin name="XIN" visible="both" length="short" direction="io" x="-12.7" y="-25.4"/>
<pin name="DM4" visible="both" length="short" direction="io" rot="R180" x="15.24" y="5.08"/>
<pin name="DP4" visible="both" length="short" direction="io" rot="R180" x="15.24" y="2.54"/>
<pin name="DM3" visible="both" length="short" direction="io" rot="R180" x="15.24" y="12.7"/>
<pin name="DP3" visible="both" length="short" direction="io" rot="R180" x="15.24" y="10.16"/>
<pin name="DM2" visible="both" length="short" direction="io" rot="R180" x="15.24" y="20.32"/>
<pin name="DP2" visible="both" length="short" direction="io" rot="R180" x="15.24" y="17.78"/>
<pin name="DM1" visible="both" length="short" direction="io" rot="R180" x="15.24" y="27.94"/>
<pin name="DP1" visible="both" length="short" direction="io" rot="R180" x="15.24" y="25.4"/>
<pin name="VD18_O" visible="both" length="short" direction="io" x="-12.7" y="-15.24"/>
<pin name="VD33" visible="both" length="short" direction="io" x="-12.7" y="-10.16"/>
<pin name="REXT" visible="both" length="short" direction="io" rot="R180" x="15.24" y="-33.02"/>
<pin name="VD18" visible="both" length="short" direction="io" x="-12.7" y="-17.78"/>
<pin name="TESTJ" visible="both" length="short" direction="io" rot="R180" x="15.24" y="-2.54"/>
<pin name="OVCJ" visible="both" length="short" direction="io" rot="R180" x="15.24" y="-5.08"/>
<pin name="PWRJ" visible="both" length="short" direction="io" rot="R180" x="15.24" y="-7.62"/>
<pin name="LED2" visible="both" length="short" direction="io" rot="R180" x="15.24" y="-15.24"/>
<pin name="LED1" visible="both" length="short" direction="io" rot="R180" x="15.24" y="-12.7"/>
<pin name="DRV" visible="both" length="short" direction="io" rot="R180" x="15.24" y="-17.78"/>
<pin name="VD33_O" visible="both" length="short" direction="io" x="-12.7" y="-7.62"/>
<pin name="VDD5" visible="both" length="short" direction="io" x="-12.7" y="-2.54"/>
<pin name="BUSJ" visible="both" length="short" direction="io" rot="R180" x="15.24" y="-22.86"/>
<pin name="VBUSM" visible="both" length="short" direction="io" rot="R180" x="15.24" y="-25.4"/>
<pin name="XRSTJ" visible="both" length="short" direction="io" rot="R180" x="15.24" y="-27.94"/>
<pin name="DPU" visible="both" length="short" direction="io" x="-12.7" y="17.78"/>
<pin name="DMU" visible="both" length="short" direction="io" x="-12.7" y="15.24"/>
</symbol>
<symbol name="Q_1">
<wire layer="94" width="0.25" x1="1.27" y1="1.016" x2="1.27" y2="-1.016"/>
<wire layer="94" width="0.25" x1="-0.762" y1="1.778" x2="0.762" y2="1.778"/>
<wire layer="94" width="0.25" x1="-1.27" y1="1.016" x2="-1.27" y2="-1.016"/>
<wire layer="94" width="0.25" x1="0.762" y1="1.778" x2="0.762" y2="-1.778"/>
<wire layer="94" width="0.25" x1="0.762" y1="-1.778" x2="-0.762" y2="-1.778"/>
<wire layer="94" width="0.25" x1="-0.762" y1="-1.778" x2="-0.762" y2="1.778"/>
<pin name="OSC1" visible="pad" length="short" direction="pas" x="-3.81" y="0"/>
<pin name="OSC2" visible="pad" length="short" direction="pas" rot="R180" x="3.81" y="0"/>
</symbol>
<symbol name="DB25M">
<wire layer="94" width="0.25" x1="-0.635" y1="30.48" x2="0.635" y2="31.75"/>
<wire layer="94" width="0.25" x1="-0.635" y1="30.48" x2="0.635" y2="29.21"/>
<wire layer="94" width="0.25" x1="-0.635" y1="30.48" x2="5.08" y2="30.48"/>
<wire layer="94" width="0.25" x1="-0.635" y1="27.94" x2="0.635" y2="29.21"/>
<wire layer="94" width="0.25" x1="-0.635" y1="27.94" x2="0.635" y2="26.67"/>
<wire layer="94" width="0.25" x1="-0.635" y1="27.94" x2="5.08" y2="27.94"/>
<wire layer="94" width="0.25" x1="-0.635" y1="25.4" x2="0.635" y2="26.67"/>
<wire layer="94" width="0.25" x1="-0.635" y1="25.4" x2="0.635" y2="24.13"/>
<wire layer="94" width="0.25" x1="-0.635" y1="25.4" x2="5.08" y2="25.4"/>
<wire layer="94" width="0.25" x1="-0.635" y1="22.86" x2="0.635" y2="24.13"/>
<wire layer="94" width="0.25" x1="-0.635" y1="22.86" x2="0.635" y2="21.59"/>
<wire layer="94" width="0.25" x1="-0.635" y1="22.86" x2="5.08" y2="22.86"/>
<wire layer="94" width="0.25" x1="-0.635" y1="20.32" x2="0.635" y2="21.59"/>
<wire layer="94" width="0.25" x1="-0.635" y1="20.32" x2="0.635" y2="19.05"/>
<wire layer="94" width="0.25" x1="-0.635" y1="20.32" x2="5.08" y2="20.32"/>
<wire layer="94" width="0.25" x1="-0.635" y1="17.78" x2="0.635" y2="19.05"/>
<wire layer="94" width="0.25" x1="-0.635" y1="17.78" x2="0.635" y2="16.51"/>
<wire layer="94" width="0.25" x1="-0.635" y1="17.78" x2="5.08" y2="17.78"/>
<wire layer="94" width="0.25" x1="-0.635" y1="15.24" x2="0.635" y2="16.51"/>
<wire layer="94" width="0.25" x1="-0.635" y1="15.24" x2="0.635" y2="13.97"/>
<wire layer="94" width="0.25" x1="-0.635" y1="15.24" x2="5.08" y2="15.24"/>
<wire layer="94" width="0.25" x1="-0.635" y1="12.7" x2="0.635" y2="13.97"/>
<wire layer="94" width="0.25" x1="-0.635" y1="12.7" x2="0.635" y2="11.43"/>
<wire layer="94" width="0.25" x1="-0.635" y1="12.7" x2="5.08" y2="12.7"/>
<wire layer="94" width="0.25" x1="-0.635" y1="10.16" x2="0.635" y2="11.43"/>
<wire layer="94" width="0.25" x1="-0.635" y1="10.16" x2="0.635" y2="8.89"/>
<wire layer="94" width="0.25" x1="-0.635" y1="10.16" x2="5.08" y2="10.16"/>
<wire layer="94" width="0.25" x1="-0.635" y1="7.62" x2="0.635" y2="8.89"/>
<wire layer="94" width="0.25" x1="-0.635" y1="7.62" x2="0.635" y2="6.35"/>
<wire layer="94" width="0.25" x1="-0.635" y1="7.62" x2="5.08" y2="7.62"/>
<wire layer="94" width="0.25" x1="-0.635" y1="5.08" x2="0.635" y2="6.35"/>
<wire layer="94" width="0.25" x1="-0.635" y1="5.08" x2="0.635" y2="3.81"/>
<wire layer="94" width="0.25" x1="-0.635" y1="5.08" x2="5.08" y2="5.08"/>
<wire layer="94" width="0.25" x1="-0.635" y1="2.54" x2="0.635" y2="3.81"/>
<wire layer="94" width="0.25" x1="-0.635" y1="2.54" x2="0.635" y2="1.27"/>
<wire layer="94" width="0.25" x1="-0.635" y1="2.54" x2="5.08" y2="2.54"/>
<wire layer="94" width="0.25" x1="-0.635" y1="0" x2="0.635" y2="1.27"/>
<wire layer="94" width="0.25" x1="-0.635" y1="0" x2="0.635" y2="-1.27"/>
<wire layer="94" width="0.25" x1="-0.635" y1="0" x2="5.08" y2="0"/>
<wire layer="94" width="0.25" x1="-0.635" y1="-2.54" x2="0.635" y2="-1.27"/>
<wire layer="94" width="0.25" x1="-0.635" y1="-2.54" x2="0.635" y2="-3.81"/>
<wire layer="94" width="0.25" x1="-0.635" y1="-2.54" x2="5.08" y2="-2.54"/>
<wire layer="94" width="0.25" x1="-0.635" y1="-5.08" x2="0.635" y2="-3.81"/>
<wire layer="94" width="0.25" x1="-0.635" y1="-5.08" x2="0.635" y2="-6.35"/>
<wire layer="94" width="0.25" x1="-0.635" y1="-5.08" x2="5.08" y2="-5.08"/>
<wire layer="94" width="0.25" x1="-0.635" y1="-7.62" x2="0.635" y2="-6.35"/>
<wire layer="94" width="0.25" x1="-0.635" y1="-7.62" x2="0.635" y2="-8.89"/>
<wire layer="94" width="0.25" x1="-0.635" y1="-7.62" x2="5.08" y2="-7.62"/>
<wire layer="94" width="0.25" x1="-0.635" y1="-10.16" x2="0.635" y2="-8.89"/>
<wire layer="94" width="0.25" x1="-0.635" y1="-10.16" x2="0.635" y2="-11.43"/>
<wire layer="94" width="0.25" x1="-0.635" y1="-10.16" x2="5.08" y2="-10.16"/>
<wire layer="94" width="0.25" x1="-0.635" y1="-12.7" x2="0.635" y2="-11.43"/>
<wire layer="94" width="0.25" x1="-0.635" y1="-12.7" x2="0.635" y2="-13.97"/>
<wire layer="94" width="0.25" x1="-0.635" y1="-12.7" x2="5.08" y2="-12.7"/>
<wire layer="94" width="0.25" x1="-0.635" y1="-15.24" x2="0.635" y2="-13.97"/>
<wire layer="94" width="0.25" x1="-0.635" y1="-15.24" x2="0.635" y2="-16.51"/>
<wire layer="94" width="0.25" x1="-0.635" y1="-15.24" x2="5.08" y2="-15.24"/>
<wire layer="94" width="0.25" x1="-0.635" y1="-17.78" x2="0.635" y2="-16.51"/>
<wire layer="94" width="0.25" x1="-0.635" y1="-17.78" x2="0.635" y2="-19.05"/>
<wire layer="94" width="0.25" x1="-0.635" y1="-17.78" x2="5.08" y2="-17.78"/>
<wire layer="94" width="0.25" x1="-0.635" y1="-20.32" x2="0.635" y2="-19.05"/>
<wire layer="94" width="0.25" x1="-0.635" y1="-20.32" x2="0.635" y2="-21.59"/>
<wire layer="94" width="0.25" x1="-0.635" y1="-20.32" x2="5.08" y2="-20.32"/>
<wire layer="94" width="0.25" x1="-0.635" y1="-22.86" x2="0.635" y2="-21.59"/>
<wire layer="94" width="0.25" x1="-0.635" y1="-22.86" x2="0.635" y2="-24.13"/>
<wire layer="94" width="0.25" x1="-0.635" y1="-22.86" x2="5.08" y2="-22.86"/>
<wire layer="94" width="0.25" x1="-0.635" y1="-25.4" x2="0.635" y2="-24.13"/>
<wire layer="94" width="0.25" x1="-0.635" y1="-25.4" x2="0.635" y2="-26.67"/>
<wire layer="94" width="0.25" x1="-0.635" y1="-25.4" x2="5.08" y2="-25.4"/>
<wire layer="94" width="0.25" x1="-0.635" y1="-27.94" x2="0.635" y2="-26.67"/>
<wire layer="94" width="0.25" x1="-0.635" y1="-27.94" x2="0.635" y2="-29.21"/>
<wire layer="94" width="0.25" x1="-0.635" y1="-27.94" x2="5.08" y2="-27.94"/>
<wire layer="94" width="0.25" x1="-0.635" y1="-30.48" x2="0.635" y2="-29.21"/>
<wire layer="94" width="0.25" x1="-0.635" y1="-30.48" x2="0.635" y2="-31.75"/>
<wire layer="94" width="0.25" x1="-0.635" y1="-30.48" x2="5.08" y2="-30.48"/>
<wire layer="94" width="0.25" x1="-5.08" y1="-35.56" x2="-5.08" y2="31.75"/>
<wire layer="94" width="0.25" x1="-5.08" y1="31.75" x2="5.08" y2="31.75"/>
<wire layer="94" width="0.25" x1="5.08" y1="31.75" x2="5.08" y2="-35.56"/>
<wire layer="94" width="0.25" x1="5.08" y1="-35.56" x2="-5.08" y2="-35.56"/>
<wire layer="94" width="0.25" x1="-0.635" y1="-33.02" x2="0.635" y2="-31.75"/>
<wire layer="94" width="0.25" x1="-0.635" y1="-33.02" x2="0.635" y2="-34.29"/>
<wire layer="94" width="0.25" x1="-0.635" y1="-33.02" x2="5.08" y2="-33.02"/>
<pin name="P1" visible="pad" length="short" direction="pas" rot="R180" x="7.62" y="30.48"/>
<pin name="P2" visible="pad" length="short" direction="pas" rot="R180" x="7.62" y="27.94"/>
<pin name="P3" visible="pad" length="short" direction="pas" rot="R180" x="7.62" y="25.4"/>
<pin name="P4" visible="pad" length="short" direction="pas" rot="R180" x="7.62" y="22.86"/>
<pin name="P5" visible="pad" length="short" direction="pas" rot="R180" x="7.62" y="20.32"/>
<pin name="P6" visible="pad" length="short" direction="pas" rot="R180" x="7.62" y="17.78"/>
<pin name="P7" visible="pad" length="short" direction="pas" rot="R180" x="7.62" y="15.24"/>
<pin name="P8" visible="pad" length="short" direction="pas" rot="R180" x="7.62" y="12.7"/>
<pin name="P9" visible="pad" length="short" direction="pas" rot="R180" x="7.62" y="10.16"/>
<pin name="P10" visible="pad" length="short" direction="pas" rot="R180" x="7.62" y="7.62"/>
<pin name="P11" visible="pad" length="short" direction="pas" rot="R180" x="7.62" y="5.08"/>
<pin name="P12" visible="pad" length="short" direction="pas" rot="R180" x="7.62" y="2.54"/>
<pin name="P13" visible="pad" length="short" direction="pas" rot="R180" x="7.62" y="0"/>
<pin name="P14" visible="pad" length="short" direction="pas" rot="R180" x="7.62" y="-2.54"/>
<pin name="P15" visible="pad" length="short" direction="pas" rot="R180" x="7.62" y="-5.08"/>
<pin name="P16" visible="pad" length="short" direction="pas" rot="R180" x="7.62" y="-7.62"/>
<pin name="P17" visible="pad" length="short" direction="pas" rot="R180" x="7.62" y="-10.16"/>
<pin name="P18" visible="pad" length="short" direction="pas" rot="R180" x="7.62" y="-12.7"/>
<pin name="P19" visible="pad" length="short" direction="pas" rot="R180" x="7.62" y="-15.24"/>
<pin name="P20" visible="pad" length="short" direction="pas" rot="R180" x="7.62" y="-17.78"/>
<pin name="P21" visible="pad" length="short" direction="pas" rot="R180" x="7.62" y="-20.32"/>
<pin name="P22" visible="pad" length="short" direction="pas" rot="R180" x="7.62" y="-22.86"/>
<pin name="P23" visible="pad" length="short" direction="pas" rot="R180" x="7.62" y="-25.4"/>
<pin name="P24" visible="pad" length="short" direction="pas" rot="R180" x="7.62" y="-27.94"/>
<pin name="P25" visible="pad" length="short" direction="pas" rot="R180" x="7.62" y="-30.48"/>
<pin name="GND" visible="pad" length="short" direction="pas" rot="R180" x="7.62" y="-33.02"/>
</symbol>
<symbol name="FPC_24_1MM">
<wire layer="94" width="0.25" x1="-3.81" y1="1.27" x2="0" y2="1.27"/>
<wire layer="94" width="0.25" x1="0" y1="1.27" x2="0" y2="-59.69"/>
<wire layer="94" width="0.25" x1="0" y1="-59.69" x2="-3.81" y2="-59.69"/>
<wire layer="94" width="0.25" x1="-3.81" y1="-59.69" x2="-3.81" y2="1.27"/>
<wire layer="94" width="0.25" x1="0" y1="1.27" x2="16.51" y2="1.27"/>
<wire layer="94" width="0.25" x1="16.51" y1="1.27" x2="16.51" y2="-59.69"/>
<wire layer="94" width="0.25" x1="16.51" y1="-59.69" x2="0" y2="-59.69"/>
<wire layer="94" width="0.25" x1="0" y1="-59.69" x2="0" y2="1.27"/>
<wire layer="94" width="0.25" x1="-3.81" y1="-1.27" x2="16.51" y2="-1.27"/>
<wire layer="94" width="0.25" x1="-3.81" y1="-3.81" x2="16.51" y2="-3.81"/>
<wire layer="94" width="0.25" x1="-3.81" y1="-6.35" x2="16.51" y2="-6.35"/>
<wire layer="94" width="0.25" x1="-3.81" y1="-8.89" x2="16.51" y2="-8.89"/>
<wire layer="94" width="0.25" x1="-3.81" y1="-11.43" x2="16.51" y2="-11.43"/>
<wire layer="94" width="0.25" x1="-3.81" y1="-13.97" x2="16.51" y2="-13.97"/>
<wire layer="94" width="0.25" x1="-3.81" y1="-16.51" x2="16.51" y2="-16.51"/>
<wire layer="94" width="0.25" x1="-3.81" y1="-19.05" x2="16.51" y2="-19.05"/>
<wire layer="94" width="0.25" x1="-3.81" y1="-21.59" x2="16.51" y2="-21.59"/>
<wire layer="94" width="0.25" x1="-3.81" y1="-24.13" x2="16.51" y2="-24.13"/>
<wire layer="94" width="0.25" x1="-3.81" y1="-26.67" x2="16.51" y2="-26.67"/>
<wire layer="94" width="0.25" x1="-3.81" y1="-29.21" x2="16.51" y2="-29.21"/>
<wire layer="94" width="0.25" x1="-3.81" y1="-31.75" x2="16.51" y2="-31.75"/>
<wire layer="94" width="0.25" x1="-3.81" y1="-34.29" x2="16.51" y2="-34.29"/>
<wire layer="94" width="0.25" x1="-3.81" y1="-36.83" x2="16.51" y2="-36.83"/>
<wire layer="94" width="0.25" x1="-3.81" y1="-39.37" x2="-2.54" y2="-39.37"/>
<wire layer="94" width="0.25" x1="16.51" y1="-39.37" x2="-2.54" y2="-39.37"/>
<wire layer="94" width="0.25" x1="-3.81" y1="-41.91" x2="16.51" y2="-41.91"/>
<wire layer="94" width="0.25" x1="-3.81" y1="-44.45" x2="16.51" y2="-44.45"/>
<wire layer="94" width="0.25" x1="-3.81" y1="-46.99" x2="16.51" y2="-46.99"/>
<wire layer="94" width="0.25" x1="-3.81" y1="-49.53" x2="16.51" y2="-49.53"/>
<wire layer="94" width="0.25" x1="-3.81" y1="-52.07" x2="16.51" y2="-52.07"/>
<wire layer="94" width="0.25" x1="-3.81" y1="-54.61" x2="16.51" y2="-54.61"/>
<wire layer="94" width="0.25" x1="-3.81" y1="-57.15" x2="16.51" y2="-57.15"/>
<pin name="1" visible="both" length="short" direction="nc" x="-6.35" y="0"/>
<pin name="2" visible="both" length="short" direction="nc" x="-6.35" y="-2.54"/>
<pin name="3" visible="both" length="short" direction="nc" x="-6.35" y="-5.08"/>
<pin name="4" visible="both" length="short" direction="nc" x="-6.35" y="-7.62"/>
<pin name="5" visible="both" length="short" direction="nc" x="-6.35" y="-10.16"/>
<pin name="6" visible="both" length="short" direction="nc" x="-6.35" y="-12.7"/>
<pin name="7" visible="both" length="short" direction="nc" x="-6.35" y="-15.24"/>
<pin name="8" visible="both" length="short" direction="nc" x="-6.35" y="-17.78"/>
<pin name="9" visible="both" length="short" direction="nc" x="-6.35" y="-20.32"/>
<pin name="10" visible="both" length="short" direction="nc" x="-6.35" y="-22.86"/>
<pin name="11" visible="both" length="short" direction="nc" x="-6.35" y="-25.4"/>
<pin name="12" visible="both" length="short" direction="nc" x="-6.35" y="-27.94"/>
<pin name="13" visible="both" length="short" direction="nc" x="-6.35" y="-30.48"/>
<pin name="14" visible="both" length="short" direction="nc" x="-6.35" y="-33.02"/>
<pin name="15" visible="both" length="short" direction="nc" x="-6.35" y="-35.56"/>
<pin name="16" visible="both" length="short" direction="nc" x="-6.35" y="-38.1"/>
<pin name="17" visible="both" length="short" direction="nc" x="-6.35" y="-40.64"/>
<pin name="18" visible="both" length="short" direction="nc" x="-6.35" y="-43.18"/>
<pin name="19" visible="both" length="short" direction="nc" x="-6.35" y="-45.72"/>
<pin name="20" visible="both" length="short" direction="nc" x="-6.35" y="-48.26"/>
<pin name="21" visible="both" length="short" direction="nc" x="-6.35" y="-50.8"/>
<pin name="22" visible="both" length="short" direction="nc" x="-6.35" y="-53.34"/>
<pin name="23" visible="both" length="short" direction="nc" x="-6.35" y="-55.88"/>
<pin name="24" visible="both" length="short" direction="nc" x="-6.35" y="-58.42"/>
</symbol>
<symbol name="PLS_16">
<wire layer="94" width="0.25" x1="-3.81" y1="1.27" x2="-3.81" y2="-39.37"/>
<wire layer="94" width="0.25" x1="-3.81" y1="-39.37" x2="0" y2="-39.37"/>
<wire layer="94" width="0.25" x1="-3.81" y1="1.27" x2="0" y2="1.27"/>
<wire layer="94" width="0.25" x1="0" y1="1.27" x2="0" y2="-39.37"/>
<wire layer="94" width="0.25" x1="0" y1="1.27" x2="16.51" y2="1.27"/>
<wire layer="94" width="0.25" x1="16.51" y1="1.27" x2="16.51" y2="-39.37"/>
<wire layer="94" width="0.25" x1="0" y1="-39.37" x2="16.51" y2="-39.37"/>
<wire layer="94" width="0.25" x1="-3.81" y1="-1.27" x2="16.51" y2="-1.27"/>
<wire layer="94" width="0.25" x1="-3.81" y1="-3.81" x2="16.51" y2="-3.81"/>
<wire layer="94" width="0.25" x1="-3.81" y1="-6.35" x2="16.51" y2="-6.35"/>
<wire layer="94" width="0.25" x1="-3.81" y1="-8.89" x2="16.51" y2="-8.89"/>
<wire layer="94" width="0.25" x1="-3.81" y1="-11.43" x2="16.51" y2="-11.43"/>
<wire layer="94" width="0.25" x1="-3.81" y1="-13.97" x2="16.51" y2="-13.97"/>
<wire layer="94" width="0.25" x1="-3.81" y1="-16.51" x2="16.51" y2="-16.51"/>
<wire layer="94" width="0.25" x1="-3.81" y1="-19.05" x2="16.51" y2="-19.05"/>
<wire layer="94" width="0.25" x1="-3.81" y1="-21.59" x2="16.51" y2="-21.59"/>
<wire layer="94" width="0.25" x1="-3.81" y1="-24.13" x2="16.51" y2="-24.13"/>
<wire layer="94" width="0.25" x1="-3.81" y1="-26.67" x2="16.51" y2="-26.67"/>
<wire layer="94" width="0.25" x1="-3.81" y1="-29.21" x2="16.51" y2="-29.21"/>
<wire layer="94" width="0.25" x1="-3.81" y1="-31.75" x2="16.51" y2="-31.75"/>
<wire layer="94" width="0.25" x1="-3.81" y1="-34.29" x2="16.51" y2="-34.29"/>
<wire layer="94" width="0.25" x1="-3.81" y1="-36.83" x2="16.51" y2="-36.83"/>
<pin name="1" visible="both" length="short" direction="nc" x="-6.35" y="0"/>
<pin name="2" visible="both" length="short" direction="nc" x="-6.35" y="-2.54"/>
<pin name="3" visible="both" length="short" direction="nc" x="-6.35" y="-5.08"/>
<pin name="4" visible="both" length="short" direction="nc" x="-6.35" y="-7.62"/>
<pin name="5" visible="both" length="short" direction="nc" x="-6.35" y="-10.16"/>
<pin name="6" visible="both" length="short" direction="nc" x="-6.35" y="-12.7"/>
<pin name="7" visible="both" length="short" direction="nc" x="-6.35" y="-15.24"/>
<pin name="8" visible="both" length="short" direction="nc" x="-6.35" y="-17.78"/>
<pin name="9" visible="both" length="short" direction="nc" x="-6.35" y="-20.32"/>
<pin name="10" visible="both" length="short" direction="nc" x="-6.35" y="-22.86"/>
<pin name="11" visible="both" length="short" direction="nc" x="-6.35" y="-25.4"/>
<pin name="12" visible="both" length="short" direction="nc" x="-6.35" y="-27.94"/>
<pin name="13" visible="both" length="short" direction="nc" x="-6.35" y="-30.48"/>
<pin name="14" visible="both" length="short" direction="nc" x="-6.35" y="-33.02"/>
<pin name="15" visible="both" length="short" direction="nc" x="-6.35" y="-35.56"/>
<pin name="16" visible="both" length="short" direction="nc" x="-6.35" y="-38.1"/>
</symbol>
<symbol name="J-1">
<wire layer="94" width="0.25" x1="8.89" y1="-5.08" x2="-0.016" y2="-5.08"/>
<wire layer="94" width="0.25" x1="-0.016" y1="-5.08" x2="-1.921" y2="-3.81"/>
<wire layer="94" width="0.25" x1="-1.921" y1="-3.81" x2="-3.826" y2="-5.08"/>
<wire layer="94" width="0.25" x1="-3.826" y1="-5.08" x2="-5.731" y2="-5.08"/>
<wire layer="94" width="0.25" x1="6.334" y1="-2.54" x2="1.889" y2="-2.54"/>
<wire layer="94" width="0.25" x1="1.889" y1="-2.54" x2="1.889" y2="-5.08"/>
<wire layer="94" width="0.25" x1="1.889" y1="-5.08" x2="1.254" y2="-3.175"/>
<wire layer="94" width="0.25" x1="1.254" y1="-3.175" x2="2.524" y2="-3.175"/>
<wire layer="94" width="0.25" x1="2.524" y1="-3.175" x2="1.889" y2="-5.08"/>
<wire layer="94" width="1.27" x1="7.604" y1="2.54" x2="-3.191" y2="2.54"/>
<wire layer="94" width="0.25" x1="-8.89" y1="6.35" x2="8.255" y2="6.35"/>
<wire layer="94" width="0.25" x1="8.255" y1="6.35" x2="8.255" y2="-6.35"/>
<wire layer="94" width="0.25" x1="8.255" y1="-6.35" x2="-8.89" y2="-6.35"/>
<wire layer="94" width="0.25" x1="-8.89" y1="-6.35" x2="-8.89" y2="6.35"/>
<wire layer="94" width="0.25" x1="8.89" y1="-2.54" x2="5.699" y2="-2.54"/>
<wire layer="94" width="0.25" x1="8.874" y1="2.54" x2="8.239" y2="2.54"/>
<pin name="1" visible="pad" length="short" direction="pwr" rot="R180" x="11.43" y="2.54"/>
<pin name="2" visible="pad" length="short" direction="pwr" rot="R180" x="11.43" y="-5.08"/>
<pin name="3" visible="pad" length="short" direction="pwr" rot="R180" x="11.43" y="-2.54"/>
</symbol>
<symbol name="MAX15070AAUT+T">
<wire layer="94" width="0.41" x1="-12.7" y1="10.16" x2="12.7" y2="10.16"/>
<wire layer="94" width="0.41" x1="12.7" y1="10.16" x2="12.7" y2="-10.16"/>
<wire layer="94" width="0.41" x1="12.7" y1="-10.16" x2="-12.7" y2="-10.16"/>
<wire layer="94" width="0.41" x1="-12.7" y1="-10.16" x2="-12.7" y2="10.16"/>
<pin name="IN+" visible="both" length="short" direction="in" x="-15.24" y="2.54"/>
<pin name="IN-" visible="both" length="short" direction="in" x="-15.24" y="0"/>
<pin name="V+" visible="both" length="short" direction="pwr" rot="R180" x="15.24" y="7.62"/>
<pin name="N_OUT" visible="both" length="short" direction="out" rot="R180" x="15.24" y="2.54"/>
<pin name="P_OUT" visible="both" length="short" direction="out" rot="R180" x="15.24" y="0"/>
<pin name="GND" visible="both" length="short" direction="pwr" rot="R180" x="15.24" y="-5.08"/>
</symbol>
<symbol name="IFX007T">
<wire layer="94" width="0.254" x1="10.16" y1="-10.16" x2="-10.16" y2="-10.16"/>
<wire layer="94" width="0.254" x1="-10.16" y1="-10.16" x2="-10.16" y2="10.16"/>
<wire layer="94" width="0.254" x1="-10.16" y1="10.16" x2="10.16" y2="10.16"/>
<wire layer="94" width="0.254" x1="10.16" y1="10.16" x2="10.16" y2="-10.16"/>
<pin name="GND" visible="both" length="short" direction="pwr" rot="R180" x="12.7" y="-7.62"/>
<pin name="IN" visible="both" length="short" direction="in" x="-12.7" y="2.54"/>
<pin name="INH" visible="both" length="short" direction="in" x="-12.7" y="0"/>
<pin name="OUT" visible="both" length="short" direction="out" rot="R180" x="12.7" y="2.54"/>
<pin name="SR" visible="both" length="short" direction="in" x="-12.7" y="-2.54"/>
<pin name="IS" visible="both" length="short" direction="out" rot="R180" x="12.7" y="-2.54"/>
<pin name="VS" visible="both" length="short" direction="pwr" rot="R180" x="12.7" y="7.62"/>
</symbol>
<symbol name="PLS_5">
<wire layer="94" width="0.25" x1="-3.81" y1="5.08" x2="-3.81" y2="-7.62"/>
<wire layer="94" width="0.25" x1="0" y1="5.08" x2="0" y2="-7.62"/>
<wire layer="94" width="0.25" x1="-3.81" y1="5.08" x2="-1.27" y2="5.08"/>
<wire layer="94" width="0.25" x1="-3.81" y1="-7.62" x2="-1.27" y2="-7.62"/>
<wire layer="94" width="0.25" x1="-3.81" y1="2.54" x2="-1.27" y2="2.54"/>
<wire layer="94" width="0.25" x1="-3.81" y1="0" x2="-1.27" y2="0"/>
<wire layer="94" width="0.25" x1="-3.81" y1="-2.54" x2="-1.27" y2="-2.54"/>
<wire layer="94" width="0.25" x1="-3.81" y1="-5.08" x2="-1.27" y2="-5.08"/>
<wire layer="94" width="0.25" x1="-1.27" y1="5.08" x2="15.24" y2="5.08"/>
<wire layer="94" width="0.25" x1="15.24" y1="5.08" x2="15.24" y2="-7.62"/>
<wire layer="94" width="0.25" x1="15.24" y1="-7.62" x2="13.97" y2="-7.62"/>
<wire layer="94" width="0.25" x1="-1.27" y1="-7.62" x2="13.97" y2="-7.62"/>
<wire layer="94" width="0.25" x1="-1.27" y1="2.54" x2="15.24" y2="2.54"/>
<wire layer="94" width="0.25" x1="-1.27" y1="0" x2="15.24" y2="0"/>
<wire layer="94" width="0.25" x1="-1.27" y1="-2.54" x2="15.24" y2="-2.54"/>
<wire layer="94" width="0.25" x1="-1.27" y1="-5.08" x2="15.24" y2="-5.08"/>
<pin name="1" visible="both" length="short" direction="nc" x="-6.35" y="3.81"/>
<pin name="2" visible="both" length="short" direction="nc" x="-6.35" y="1.27"/>
<pin name="3" visible="both" length="short" direction="nc" x="-6.35" y="-1.27"/>
<pin name="4" visible="both" length="short" direction="nc" x="-6.35" y="-3.81"/>
<pin name="5" visible="both" length="short" direction="nc" x="-6.35" y="-6.35"/>
</symbol>
<symbol name="CAP_0805_1206">
<wire layer="94" width="0.25" x1="-0.317" y1="-1.905" x2="-0.317" y2="1.905"/>
<wire layer="94" width="0.25" x1="0.317" y1="-1.905" x2="0.317" y2="1.905"/>
<wire layer="94" width="0.25" x1="0.318" y1="0" x2="1.27" y2="0"/>
<wire layer="94" width="0.25" x1="-1.27" y1="0" x2="-0.317" y2="0"/>
<pin name="1" visible="pad" length="short" direction="pas" x="-3.81" y="0"/>
<pin name="2" visible="pad" length="short" direction="pas" rot="R180" x="3.81" y="0"/>
</symbol>
<symbol name="PILL_STM32G431">
<wire layer="94" width="0.25" x1="-20.342" y1="25.392" x2="-14.95" y2="25.392"/>
<wire layer="94" width="0.25" x1="-14.95" y1="25.392" x2="-14.95" y2="-25.424"/>
<wire layer="94" width="0.25" x1="-14.95" y1="-25.424" x2="-20.342" y2="-25.424"/>
<wire layer="94" width="0.25" x1="-20.342" y1="-25.424" x2="-20.342" y2="25.392"/>
<wire layer="94" width="0.25" x1="-14.95" y1="25.392" x2="-0.022" y2="25.392"/>
<wire layer="94" width="0.25" x1="-0.022" y1="25.392" x2="-0.022" y2="-25.424"/>
<wire layer="94" width="0.25" x1="-0.022" y1="-25.424" x2="-14.95" y2="-25.424"/>
<wire layer="94" width="0.25" x1="-14.95" y1="-25.424" x2="-14.95" y2="25.392"/>
<wire layer="94" width="0.25" x1="-20.342" y1="22.836" x2="-0.022" y2="22.836"/>
<wire layer="94" width="0.25" x1="-20.342" y1="20.296" x2="-0.022" y2="20.296"/>
<wire layer="94" width="0.25" x1="-20.342" y1="17.756" x2="-0.022" y2="17.756"/>
<wire layer="94" width="0.25" x1="-20.342" y1="15.216" x2="-19.072" y2="15.216"/>
<wire layer="94" width="0.25" x1="-0.022" y1="15.216" x2="-19.072" y2="15.216"/>
<wire layer="94" width="0.25" x1="-20.342" y1="12.676" x2="-0.022" y2="12.676"/>
<wire layer="94" width="0.25" x1="-20.342" y1="10.136" x2="-0.022" y2="10.136"/>
<wire layer="94" width="0.25" x1="-20.342" y1="7.596" x2="-0.022" y2="7.596"/>
<wire layer="94" width="0.25" x1="-20.342" y1="5.056" x2="-0.022" y2="5.056"/>
<wire layer="94" width="0.25" x1="-20.342" y1="2.516" x2="-0.022" y2="2.516"/>
<wire layer="94" width="0.25" x1="-20.342" y1="-0.024" x2="-0.022" y2="-0.024"/>
<wire layer="94" width="0.25" x1="-20.342" y1="-2.564" x2="-0.022" y2="-2.564"/>
<wire layer="94" width="0.25" x1="-20.342" y1="-5.104" x2="-0.022" y2="-5.104"/>
<wire layer="94" width="0.25" x1="-20.342" y1="-7.644" x2="-0.022" y2="-7.644"/>
<wire layer="94" width="0.25" x1="-20.342" y1="-10.184" x2="-0.022" y2="-10.184"/>
<wire layer="94" width="0.25" x1="-20.342" y1="-12.724" x2="-0.022" y2="-12.724"/>
<wire layer="94" width="0.25" x1="-20.342" y1="-15.264" x2="-0.022" y2="-15.264"/>
<wire layer="94" width="0.25" x1="-20.342" y1="-17.804" x2="-0.022" y2="-17.804"/>
<wire layer="94" width="0.25" x1="-20.342" y1="-20.344" x2="-0.022" y2="-20.344"/>
<wire layer="94" width="0.25" x1="-20.342" y1="-22.884" x2="-0.022" y2="-22.884"/>
<wire layer="94" width="0.25" x1="14.91" y1="25.394" x2="20.302" y2="25.394"/>
<wire layer="94" width="0.25" x1="20.302" y1="25.394" x2="20.302" y2="-25.422"/>
<wire layer="94" width="0.25" x1="20.302" y1="-25.422" x2="14.91" y2="-25.422"/>
<wire layer="94" width="0.25" x1="14.91" y1="-25.422" x2="14.91" y2="25.394"/>
<wire layer="94" width="0.25" x1="-0.018" y1="25.394" x2="14.91" y2="25.394"/>
<wire layer="94" width="0.25" x1="14.91" y1="25.394" x2="14.91" y2="-25.422"/>
<wire layer="94" width="0.25" x1="14.91" y1="-25.422" x2="-0.018" y2="-25.422"/>
<wire layer="94" width="0.25" x1="-0.018" y1="-25.422" x2="-0.018" y2="25.394"/>
<wire layer="94" width="0.25" x1="20.302" y1="-22.866" x2="-0.018" y2="-22.866"/>
<wire layer="94" width="0.25" x1="20.302" y1="-20.326" x2="-0.018" y2="-20.326"/>
<wire layer="94" width="0.25" x1="20.302" y1="-17.786" x2="-0.018" y2="-17.786"/>
<wire layer="94" width="0.25" x1="20.302" y1="-15.246" x2="19.032" y2="-15.246"/>
<wire layer="94" width="0.25" x1="-0.018" y1="-15.246" x2="19.032" y2="-15.246"/>
<wire layer="94" width="0.25" x1="20.302" y1="-12.706" x2="-0.018" y2="-12.706"/>
<wire layer="94" width="0.25" x1="20.302" y1="-10.166" x2="-0.018" y2="-10.166"/>
<wire layer="94" width="0.25" x1="20.302" y1="-7.626" x2="-0.018" y2="-7.626"/>
<wire layer="94" width="0.25" x1="20.302" y1="-5.086" x2="-0.018" y2="-5.086"/>
<wire layer="94" width="0.25" x1="20.302" y1="-2.546" x2="-0.018" y2="-2.546"/>
<wire layer="94" width="0.25" x1="20.302" y1="-0.006" x2="-0.018" y2="-0.006"/>
<wire layer="94" width="0.25" x1="20.302" y1="2.534" x2="-0.018" y2="2.534"/>
<wire layer="94" width="0.25" x1="20.302" y1="5.074" x2="-0.018" y2="5.074"/>
<wire layer="94" width="0.25" x1="20.302" y1="7.614" x2="-0.018" y2="7.614"/>
<wire layer="94" width="0.25" x1="20.302" y1="10.154" x2="-0.018" y2="10.154"/>
<wire layer="94" width="0.25" x1="20.302" y1="12.694" x2="-0.018" y2="12.694"/>
<wire layer="94" width="0.25" x1="20.302" y1="15.234" x2="-0.018" y2="15.234"/>
<wire layer="94" width="0.25" x1="20.302" y1="17.774" x2="-0.018" y2="17.774"/>
<wire layer="94" width="0.25" x1="20.302" y1="20.314" x2="-0.018" y2="20.314"/>
<wire layer="94" width="0.25" x1="20.302" y1="22.854" x2="-0.018" y2="22.854"/>
<pin name="B12" visible="both" length="short" direction="nc" x="-22.882" y="24.106"/>
<pin name="B13" visible="both" length="short" direction="nc" x="-22.882" y="21.584"/>
<pin name="B14" visible="both" length="short" direction="nc" x="-22.882" y="19.026"/>
<pin name="B15" visible="both" length="short" direction="nc" x="-22.882" y="16.486"/>
<pin name="A8" visible="both" length="short" direction="nc" x="-22.882" y="13.964"/>
<pin name="A9" visible="both" length="short" direction="nc" x="-22.882" y="11.406"/>
<pin name="A10" visible="both" length="short" direction="nc" x="-22.882" y="8.866"/>
<pin name="A11" visible="both" length="short" direction="nc" x="-22.882" y="6.326"/>
<pin name="A12" visible="both" length="short" direction="nc" x="-22.882" y="3.786"/>
<pin name="A15" visible="both" length="short" direction="nc" x="-22.882" y="1.246"/>
<pin name="B3" visible="both" length="short" direction="nc" x="-22.882" y="-1.276"/>
<pin name="B4" visible="both" length="short" direction="nc" x="-22.882" y="-3.816"/>
<pin name="B5" visible="both" length="short" direction="nc" x="-22.882" y="-6.356"/>
<pin name="B6" visible="both" length="short" direction="nc" x="-22.882" y="-8.896"/>
<pin name="B7" visible="both" length="short" direction="nc" x="-22.882" y="-11.436"/>
<pin name="B8" visible="both" length="short" direction="nc" x="-22.882" y="-13.976"/>
<pin name="B9" visible="both" length="short" direction="nc" x="-22.882" y="-16.516"/>
<pin name="5v" visible="both" length="short" direction="nc" x="-22.882" y="-19.074"/>
<pin name="G@1" visible="both" length="short" direction="nc" x="-22.882" y="-21.614"/>
<pin name="3.3v@1" visible="both" length="short" direction="nc" x="-22.882" y="-24.136"/>
<pin name="BAT" visible="both" length="short" direction="nc" rot="R180" x="22.842" y="-24.136"/>
<pin name="C13" visible="both" length="short" direction="nc" rot="R180" x="22.842" y="-21.614"/>
<pin name="C14" visible="both" length="short" direction="nc" rot="R180" x="22.842" y="-19.056"/>
<pin name="C15" visible="both" length="short" direction="nc" rot="R180" x="22.842" y="-16.516"/>
<pin name="A0" visible="both" length="short" direction="nc" rot="R180" x="22.842" y="-13.976"/>
<pin name="A1" visible="both" length="short" direction="nc" rot="R180" x="22.842" y="-11.436"/>
<pin name="A2" visible="both" length="short" direction="nc" rot="R180" x="22.842" y="-8.896"/>
<pin name="A3" visible="both" length="short" direction="nc" rot="R180" x="22.842" y="-6.356"/>
<pin name="A4" visible="both" length="short" direction="nc" rot="R180" x="22.842" y="-3.816"/>
<pin name="A5" visible="both" length="short" direction="nc" rot="R180" x="22.842" y="-1.276"/>
<pin name="A6" visible="both" length="short" direction="nc" rot="R180" x="22.842" y="1.264"/>
<pin name="A7" visible="both" length="short" direction="nc" rot="R180" x="22.842" y="3.804"/>
<pin name="B0" visible="both" length="short" direction="nc" rot="R180" x="22.842" y="6.344"/>
<pin name="B1" visible="both" length="short" direction="nc" rot="R180" x="22.842" y="8.866"/>
<pin name="B2" visible="both" length="short" direction="nc" rot="R180" x="22.842" y="11.406"/>
<pin name="B10" visible="both" length="short" direction="nc" rot="R180" x="22.842" y="13.964"/>
<pin name="B11" visible="both" length="short" direction="nc" rot="R180" x="22.842" y="16.504"/>
<pin name="R" visible="both" length="short" direction="nc" rot="R180" x="22.842" y="19.044"/>
<pin name="3.3v@2" visible="both" length="short" direction="nc" rot="R180" x="22.842" y="21.584"/>
<pin name="G@2" visible="both" length="short" direction="nc" rot="R180" x="22.842" y="24.106"/>
</symbol>
<symbol name="+19V">
<wire layer="94" width="0.25" x1="-2.54" y1="0" x2="2.54" y2="0"/>
<pin name="+24V" visible="pad" length="short" direction="sup" rot="R90" x="0" y="-2.54"/>
</symbol>
</symbols>
<devicesets>
<deviceset name="USB-1_TYPE_B" prefix="USB_IN">
<gates>
<gate name="PART_1" symbol="USB-1_TYPE_B" x="0" y="0"/>
</gates>
<devices>
<device name="" package="USB-1_TYPE_B">
<connects>
<connect gate="PART_1" pin="VBUS" pad="1"/>
<connect gate="PART_1" pin="D-" pad="2"/>
<connect gate="PART_1" pin="D+" pad="3"/>
<connect gate="PART_1" pin="CASE" pad="5"/>
<connect gate="PART_1" pin="GND" pad="4"/>
</connects>
<technologies>
<technology name="">
<attribute name="VALUE" value="Type B, Receptacle"/>
<attribute name="PART_NUMBER_(DIGI-KEY)" value="A123109-ND"/>
<attribute name="UNIQUE_NAME" value="TE_1734366-4"/>
</technology>
</technologies>
</device>
</devices>
</deviceset>
<deviceset name="+5V" prefix="NetPort">
<gates>
<gate name="PART_1" symbol="+5V" x="0" y="0"/>
</gates>
<devices>
<device name="">
<connects/>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
<deviceset name="R_0805_1206" prefix="R">
<gates>
<gate name="PART_1" symbol="R_0805_1206" x="0" y="0"/>
</gates>
<devices>
<device name="" package="R_0805_1206">
<connects>
<connect gate="PART_1" pin="2" pad="2@_1"/>
<connect gate="PART_1" pin="1" pad="1@_1"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
<deviceset name="PLS_2" prefix="USBPULLUP">
<gates>
<gate name="PART_1" symbol="PLS_2" x="0" y="0"/>
</gates>
<devices>
<device name="" package="PLS_2">
<connects>
<connect gate="PART_1" pin="1" pad="1"/>
<connect gate="PART_1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name="">
<attribute name="VALUE" value="USB PULLUP"/>
<attribute name="WEB" value="http://vinratel.at.ua/"/>
<attribute name="AUTHOR" value="Даньковский В.И."/>
<attribute name="MAIL" value="dvi534538@mail/ru"/>
</technology>
</technologies>
</device>
</devices>
</deviceset>
<deviceset name="USB-1_TYPE_A" prefix="J">
<gates>
<gate name="PART_1" symbol="USB-1_TYPE_A" x="0" y="0"/>
</gates>
<devices>
<device name="" package="USB-1_TYPE_A">
<connects>
<connect gate="PART_1" pin="VBUS" pad="1"/>
<connect gate="PART_1" pin="D-" pad="2"/>
<connect gate="PART_1" pin="D+" pad="3"/>
<connect gate="PART_1" pin="CASE" pad="5@_1"/>
<connect gate="PART_1" pin="GND" pad="4"/>
</connects>
<technologies>
<technology name="">
<attribute name="VALUE" value="USB Type A"/>
<attribute name="PART_NUMBER_(DIGI-KEY)" value="A123109-ND"/>
<attribute name="UNIQUE_NAME" value="TE_1734366-4"/>
</technology>
</technologies>
</device>
</devices>
</deviceset>
<deviceset name="CAP_P_5MM" prefix="C">
<gates>
<gate name="PART_1" symbol="CAP_P_5MM" x="0" y="0"/>
</gates>
<devices>
<device name="" package="CAP_P_5MM">
<connects>
<connect gate="PART_1" pin="PLUS" pad="1"/>
<connect gate="PART_1" pin="MINUS" pad="2"/>
</connects>
<technologies>
<technology name="">
<attribute name="VALUE" value="1000 mf"/>
</technology>
</technologies>
</device>
</devices>
</deviceset>
<deviceset name="CAP_P_3MM" prefix="C">
<gates>
<gate name="PART_1" symbol="CAP_P_3MM" x="0" y="0"/>
</gates>
<devices>
<device name="" package="CAP_P_3MM">
<connects>
<connect gate="PART_1" pin="PLUS" pad="1"/>
<connect gate="PART_1" pin="MINUS" pad="2"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
<deviceset name="2_SCREW_TERM._BLK." prefix="DC">
<gates>
<gate name="PART_1" symbol="2_SCREW_TERM._BLK." x="0" y="0"/>
</gates>
<devices>
<device name="" package="2_SCREW_TERM._BLK.">
<connects>
<connect gate="PART_1" pin="2" pad="2"/>
<connect gate="PART_1" pin="1" pad="1"/>
</connects>
<technologies>
<technology name="">
<attribute name="VALUE" value="DC"/>
</technology>
</technologies>
</device>
</devices>
</deviceset>
<deviceset name="PLS_3" prefix="ENCKP">
<gates>
<gate name="PART_1" symbol="PLS_3" x="-3.81" y="0"/>
</gates>
<devices>
<device name="" package="PLS_3">
<connects>
<connect gate="PART_1" pin="1" pad="1"/>
<connect gate="PART_1" pin="2" pad="2"/>
<connect gate="PART_1" pin="3" pad="3"/>
</connects>
<technologies>
<technology name="">
<attribute name="VALUE" value="ENCKP"/>
<attribute name="WEB" value="http://vinratel.at.ua/"/>
<attribute name="AUTHOR" value="Даньковский В.И."/>
<attribute name="MAIL" value="dvi534538@mail/ru"/>
</technology>
</technologies>
</device>
</devices>
</deviceset>
<deviceset name="CAP_SMD_P_5MM" prefix="C">
<gates>
<gate name="PART_1" symbol="CAP_SMD_P_5MM" x="0" y="0"/>
</gates>
<devices>
<device name="" package="СAP_P_SMD_5MM">
<connects>
<connect gate="PART_1" pin="PLUS" pad="1@"/>
<connect gate="PART_1" pin="MINUS" pad="2@"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
<deviceset name="GND" prefix="NetPort">
<gates>
<gate name="PART_1" symbol="GND" x="0" y="0"/>
</gates>
<devices>
<device name="">
<connects/>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
<deviceset name="BLUE_PILL_STM32F103" prefix="U">
<gates>
<gate name="PART_1" symbol="BLUE_PILL_STM32F103" x="0.02" y="0.015"/>
</gates>
<devices>
<device name="" package="ST_PILL">
<connects>
<connect gate="PART_1" pin="B12" pad="1"/>
<connect gate="PART_1" pin="B13" pad="2"/>
<connect gate="PART_1" pin="B14" pad="3"/>
<connect gate="PART_1" pin="B15" pad="4"/>
<connect gate="PART_1" pin="A8" pad="5"/>
<connect gate="PART_1" pin="A9" pad="6"/>
<connect gate="PART_1" pin="A10" pad="7"/>
<connect gate="PART_1" pin="A11" pad="8"/>
<connect gate="PART_1" pin="A12" pad="9"/>
<connect gate="PART_1" pin="A15" pad="10"/>
<connect gate="PART_1" pin="B3" pad="11"/>
<connect gate="PART_1" pin="B4" pad="12"/>
<connect gate="PART_1" pin="B5" pad="13"/>
<connect gate="PART_1" pin="B6" pad="14"/>
<connect gate="PART_1" pin="B7" pad="15"/>
<connect gate="PART_1" pin="B8" pad="16"/>
<connect gate="PART_1" pin="B9" pad="17"/>
<connect gate="PART_1" pin="5v" pad="18"/>
<connect gate="PART_1" pin="G@1" pad="19"/>
<connect gate="PART_1" pin="3.3v@1" pad="20"/>
<connect gate="PART_1" pin="BAT" pad="21"/>
<connect gate="PART_1" pin="C13" pad="22"/>
<connect gate="PART_1" pin="C14" pad="23"/>
<connect gate="PART_1" pin="C15" pad="24"/>
<connect gate="PART_1" pin="A0" pad="25"/>
<connect gate="PART_1" pin="A1" pad="26"/>
<connect gate="PART_1" pin="A2" pad="27"/>
<connect gate="PART_1" pin="A3" pad="28"/>
<connect gate="PART_1" pin="A4" pad="29"/>
<connect gate="PART_1" pin="A5" pad="30"/>
<connect gate="PART_1" pin="A6" pad="31"/>
<connect gate="PART_1" pin="A7" pad="32"/>
<connect gate="PART_1" pin="B0" pad="33"/>
<connect gate="PART_1" pin="B1" pad="34"/>
<connect gate="PART_1" pin="B10" pad="35"/>
<connect gate="PART_1" pin="B11" pad="36"/>
<connect gate="PART_1" pin="R" pad="37"/>
<connect gate="PART_1" pin="3.3v@2" pad="38"/>
<connect gate="PART_1" pin="G@2" pad="39"/>
<connect gate="PART_1" pin="G@3" pad="40"/>
</connects>
<technologies>
<technology name="">
<attribute name="VALUE" value="Blue Pill STM32F103"/>
</technology>
</technologies>
</device>
</devices>
</deviceset>
<deviceset name="FE1.1S" prefix="IC">
<gates>
<gate name="PART_1" symbol="FE1.1S" x="-1.27" y="2.54"/>
</gates>
<devices>
<device name="" package="SOP64P600X175-28N">
<connects>
<connect gate="PART_1" pin="VSS" pad="1"/>
<connect gate="PART_1" pin="XOUT" pad="2"/>
<connect gate="PART_1" pin="XIN" pad="3"/>
<connect gate="PART_1" pin="DM4" pad="4"/>
<connect gate="PART_1" pin="DP4" pad="5"/>
<connect gate="PART_1" pin="DM3" pad="6"/>
<connect gate="PART_1" pin="DP3" pad="7"/>
<connect gate="PART_1" pin="DM2" pad="8"/>
<connect gate="PART_1" pin="DP2" pad="9"/>
<connect gate="PART_1" pin="DM1" pad="10"/>
<connect gate="PART_1" pin="DP1" pad="11"/>
<connect gate="PART_1" pin="VD18_O" pad="12"/>
<connect gate="PART_1" pin="VD33" pad="13"/>
<connect gate="PART_1" pin="REXT" pad="14"/>
<connect gate="PART_1" pin="VD18" pad="28"/>
<connect gate="PART_1" pin="TESTJ" pad="27"/>
<connect gate="PART_1" pin="OVCJ" pad="26"/>
<connect gate="PART_1" pin="PWRJ" pad="25"/>
<connect gate="PART_1" pin="LED2" pad="24"/>
<connect gate="PART_1" pin="LED1" pad="23"/>
<connect gate="PART_1" pin="DRV" pad="22"/>
<connect gate="PART_1" pin="VD33_O" pad="21"/>
<connect gate="PART_1" pin="VDD5" pad="20"/>
<connect gate="PART_1" pin="BUSJ" pad="19"/>
<connect gate="PART_1" pin="VBUSM" pad="18"/>
<connect gate="PART_1" pin="XRSTJ" pad="17"/>
<connect gate="PART_1" pin="DPU" pad="16"/>
<connect gate="PART_1" pin="DMU" pad="15"/>
</connects>
<technologies>
<technology name="">
<attribute name="VALUE" value="FE1.1S"/>
<attribute name="MF" value="terminus"/>
<attribute name="DESCRIPTION" value="
                        
                            USB 2.0 HIGH SPEED 4-PORT HUB CONTROLLER
                        
                    "/>
<attribute name="PACKAGE" value="None"/>
<attribute name="PRICE" value="None"/>
<attribute name="SNAPEDA_LINK" value="https://www.snapeda.com/parts/FE1.1S/Terminus/view-part/?ref=snap"/>
<attribute name="MP" value="FE1.1S"/>
<attribute name="AVAILABILITY" value="In Stock"/>
<attribute name="CHECK_PRICES" value="https://www.snapeda.com/parts/FE1.1S/Terminus/view-part/?ref=eda"/>
</technology>
</technologies>
</device>
</devices>
</deviceset>
<deviceset name="Q_1" prefix="Z">
<gates>
<gate name="PART_1" symbol="Q_1" x="0" y="0"/>
</gates>
<devices>
<device name="" package="Q_1">
<connects>
<connect gate="PART_1" pin="OSC1" pad="1"/>
<connect gate="PART_1" pin="OSC2" pad="2"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
<deviceset name="DB25M" prefix="DB">
<gates>
<gate name="PART_1" symbol="DB25M" x="0" y="1.905"/>
</gates>
<devices>
<device name="" package="DB25M">
<connects>
<connect gate="PART_1" pin="P1" pad="1"/>
<connect gate="PART_1" pin="P2" pad="2"/>
<connect gate="PART_1" pin="P3" pad="3"/>
<connect gate="PART_1" pin="P4" pad="4"/>
<connect gate="PART_1" pin="P5" pad="5"/>
<connect gate="PART_1" pin="P6" pad="6"/>
<connect gate="PART_1" pin="P7" pad="7"/>
<connect gate="PART_1" pin="P8" pad="8"/>
<connect gate="PART_1" pin="P9" pad="9"/>
<connect gate="PART_1" pin="P10" pad="10"/>
<connect gate="PART_1" pin="P11" pad="11"/>
<connect gate="PART_1" pin="P12" pad="12"/>
<connect gate="PART_1" pin="P13" pad="13"/>
<connect gate="PART_1" pin="P14" pad="14"/>
<connect gate="PART_1" pin="P15" pad="15"/>
<connect gate="PART_1" pin="P16" pad="16"/>
<connect gate="PART_1" pin="P17" pad="17"/>
<connect gate="PART_1" pin="P18" pad="18"/>
<connect gate="PART_1" pin="P19" pad="19"/>
<connect gate="PART_1" pin="P20" pad="20"/>
<connect gate="PART_1" pin="P21" pad="21"/>
<connect gate="PART_1" pin="P22" pad="22"/>
<connect gate="PART_1" pin="P23" pad="23"/>
<connect gate="PART_1" pin="P24" pad="24"/>
<connect gate="PART_1" pin="P25" pad="25"/>
<connect gate="PART_1" pin="GND" pad="@26_1"/>
</connects>
<technologies>
<technology name="">
<attribute name="VALUE" value="DB25M"/>
<attribute name="UNIQUE_NAME" value="TE_DB25M"/>
</technology>
</technologies>
</device>
</devices>
</deviceset>
<deviceset name="FPC_24_1MM" prefix="FPC">
<gates>
<gate name="PART_1" symbol="FPC_24_1MM" x="-6.35" y="29.21"/>
</gates>
<devices>
<device name="" package="FPC_24_1MM">
<connects>
<connect gate="PART_1" pin="1" pad="1"/>
<connect gate="PART_1" pin="2" pad="2"/>
<connect gate="PART_1" pin="3" pad="3"/>
<connect gate="PART_1" pin="4" pad="4"/>
<connect gate="PART_1" pin="5" pad="5"/>
<connect gate="PART_1" pin="6" pad="6"/>
<connect gate="PART_1" pin="7" pad="7"/>
<connect gate="PART_1" pin="8" pad="8"/>
<connect gate="PART_1" pin="9" pad="9"/>
<connect gate="PART_1" pin="10" pad="10"/>
<connect gate="PART_1" pin="11" pad="11"/>
<connect gate="PART_1" pin="12" pad="12"/>
<connect gate="PART_1" pin="13" pad="13"/>
<connect gate="PART_1" pin="14" pad="14"/>
<connect gate="PART_1" pin="15" pad="15"/>
<connect gate="PART_1" pin="16" pad="16"/>
<connect gate="PART_1" pin="17" pad="17"/>
<connect gate="PART_1" pin="18" pad="18"/>
<connect gate="PART_1" pin="19" pad="19"/>
<connect gate="PART_1" pin="20" pad="20"/>
<connect gate="PART_1" pin="21" pad="21"/>
<connect gate="PART_1" pin="22" pad="22"/>
<connect gate="PART_1" pin="23" pad="23"/>
<connect gate="PART_1" pin="24" pad="24"/>
</connects>
<technologies>
<technology name="">
<attribute name="VALUE" value="FPC 24 1mm"/>
<attribute name="PART_NUMBER_(DIGI-KEY)" value="A123109-ND"/>
<attribute name="UNIQUE_NAME" value="TE_1734366-4"/>
</technology>
</technologies>
</device>
</devices>
</deviceset>
<deviceset name="PLS_16" prefix="STEPPERSHIELD">
<gates>
<gate name="PART_1" symbol="PLS_16" x="-6.35" y="19.05"/>
</gates>
<devices>
<device name="" package="PLS_16">
<connects>
<connect gate="PART_1" pin="1" pad="1"/>
<connect gate="PART_1" pin="2" pad="2"/>
<connect gate="PART_1" pin="3" pad="3"/>
<connect gate="PART_1" pin="4" pad="4"/>
<connect gate="PART_1" pin="5" pad="5"/>
<connect gate="PART_1" pin="6" pad="6"/>
<connect gate="PART_1" pin="7" pad="7"/>
<connect gate="PART_1" pin="8" pad="8"/>
<connect gate="PART_1" pin="9" pad="9"/>
<connect gate="PART_1" pin="10" pad="10"/>
<connect gate="PART_1" pin="11" pad="11"/>
<connect gate="PART_1" pin="12" pad="12"/>
<connect gate="PART_1" pin="13" pad="13"/>
<connect gate="PART_1" pin="14" pad="14"/>
<connect gate="PART_1" pin="15" pad="15"/>
<connect gate="PART_1" pin="16" pad="16"/>
</connects>
<technologies>
<technology name="">
<attribute name="VALUE" value="STEPPER SHIELD"/>
<attribute name="WEB" value="http://vinratel.at.ua/"/>
<attribute name="AUTHOR" value="Даньковский В.И."/>
<attribute name="MAIL" value="dvi534538@mail/ru"/>
</technology>
</technologies>
</device>
</devices>
</deviceset>
<deviceset name="J-1" prefix="DCIN">
<gates>
<gate name="PART_1" symbol="J-1" x="0" y="0"/>
</gates>
<devices>
<device name="" package="J-1">
<connects>
<connect gate="PART_1" pin="1" pad="1"/>
<connect gate="PART_1" pin="2" pad="2"/>
<connect gate="PART_1" pin="3" pad="3"/>
</connects>
<technologies>
<technology name="">
<attribute name="VALUE" value="DC IN"/>
</technology>
</technologies>
</device>
</devices>
</deviceset>
<deviceset name="MAX15070AAUT+T" prefix="U">
<gates>
<gate name="PART_1" symbol="MAX15070AAUT+T" x="0" y="0"/>
</gates>
<devices>
<device name="" package="SOT95P280X145-6N">
<connects>
<connect gate="PART_1" pin="IN+" pad="1"/>
<connect gate="PART_1" pin="IN-" pad="3"/>
<connect gate="PART_1" pin="V+" pad="6"/>
<connect gate="PART_1" pin="N_OUT" pad="4"/>
<connect gate="PART_1" pin="P_OUT" pad="5"/>
<connect gate="PART_1" pin="GND" pad="2"/>
</connects>
<technologies>
<technology name="">
<attribute name="VALUE" value="MAX15070"/>
<attribute name="MF" value="Maxim Integrated Products"/>
<attribute name="DESCRIPTION" value="
                        
                            Low-Side Gate Driver IC Inverting, Non-Inverting SOT-23-6
                        
                    "/>
<attribute name="PACKAGE" value="SOT-23-6 Maxim Integrated"/>
<attribute name="PRICE" value="None"/>
<attribute name="SNAPEDA_LINK" value="https://www.snapeda.com/parts/MAX15070AAUT+T/Maxim+Integrated/view-part/?ref=snap"/>
<attribute name="MP" value="MAX15070AAUT+T"/>
<attribute name="AVAILABILITY" value="In Stock"/>
<attribute name="CHECK_PRICES" value="https://www.snapeda.com/parts/MAX15070AAUT+T/Maxim+Integrated/view-part/?ref=eda"/>
</technology>
</technologies>
</device>
</devices>
</deviceset>
<deviceset name="IFX007T" prefix="U">
<gates>
<gate name="PART_1" symbol="IFX007T" x="0" y="0"/>
</gates>
<devices>
<device name="" package="TO127P1500X440-8N">
<connects>
<connect gate="PART_1" pin="GND" pad="1"/>
<connect gate="PART_1" pin="IN" pad="2"/>
<connect gate="PART_1" pin="INH" pad="3"/>
<connect gate="PART_1" pin="OUT" pad="4 8"/>
<connect gate="PART_1" pin="SR" pad="5"/>
<connect gate="PART_1" pin="IS" pad="6"/>
<connect gate="PART_1" pin="VS" pad="7"/>
</connects>
<technologies>
<technology name="">
<attribute name="VALUE" value="IFX007T"/>
<attribute name="MF" value="Infineon Technologies"/>
<attribute name="DESCRIPTION" value="
                        
                            Half Bridge Driver DC Motors, General Purpose Power MOSFET PG-TO263-7-1
                        
                    "/>
<attribute name="PACKAGE" value="TO-263-8 Infineon Technologies"/>
<attribute name="PRICE" value="None"/>
<attribute name="SNAPEDA_LINK" value="https://www.snapeda.com/parts/IFX007T/Infineon/view-part/?ref=snap"/>
<attribute name="MP" value="IFX007T"/>
<attribute name="AVAILABILITY" value="Not in stock"/>
<attribute name="CHECK_PRICES" value="https://www.snapeda.com/parts/IFX007T/Infineon/view-part/?ref=eda"/>
</technology>
</technologies>
</device>
</devices>
</deviceset>
<deviceset name="PLS_5" prefix="BLDC">
<gates>
<gate name="PART_1" symbol="PLS_5" x="-5.715" y="1.27"/>
</gates>
<devices>
<device name="" package="PLS_5">
<connects>
<connect gate="PART_1" pin="1" pad="1"/>
<connect gate="PART_1" pin="2" pad="2"/>
<connect gate="PART_1" pin="3" pad="3"/>
<connect gate="PART_1" pin="4" pad="4"/>
<connect gate="PART_1" pin="5" pad="5"/>
</connects>
<technologies>
<technology name="">
<attribute name="VALUE" value="BLDC  SHIELD"/>
<attribute name="WEB" value="http://vinratel.at.ua/"/>
<attribute name="AUTHOR" value="Даньковский В.И."/>
<attribute name="MAIL" value="dvi534538@mail/ru"/>
</technology>
</technologies>
</device>
</devices>
</deviceset>
<deviceset name="CAP_0805_1206" prefix="C">
<gates>
<gate name="PART_1" symbol="CAP_0805_1206" x="0" y="0"/>
</gates>
<devices>
<device name="" package="СAP_0805_1206">
<connects>
<connect gate="PART_1" pin="1" pad="1@_1"/>
<connect gate="PART_1" pin="2" pad="2@_1"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
<deviceset name="PILL_STM32G431" prefix="U">
<gates>
<gate name="PART_1" symbol="PILL_STM32G431" x="0.02" y="0.015"/>
</gates>
<devices>
<device name="" package="ST_PILL">
<connects>
<connect gate="PART_1" pin="B12" pad="1"/>
<connect gate="PART_1" pin="B13" pad="2"/>
<connect gate="PART_1" pin="B14" pad="3"/>
<connect gate="PART_1" pin="B15" pad="4"/>
<connect gate="PART_1" pin="A8" pad="5"/>
<connect gate="PART_1" pin="A9" pad="6"/>
<connect gate="PART_1" pin="A10" pad="7"/>
<connect gate="PART_1" pin="A11" pad="8"/>
<connect gate="PART_1" pin="A12" pad="9"/>
<connect gate="PART_1" pin="A15" pad="10"/>
<connect gate="PART_1" pin="B3" pad="11"/>
<connect gate="PART_1" pin="B4" pad="12"/>
<connect gate="PART_1" pin="B5" pad="13"/>
<connect gate="PART_1" pin="B6" pad="14"/>
<connect gate="PART_1" pin="B7" pad="15"/>
<connect gate="PART_1" pin="B8" pad="16"/>
<connect gate="PART_1" pin="B9" pad="17"/>
<connect gate="PART_1" pin="5v" pad="18"/>
<connect gate="PART_1" pin="G@1" pad="19"/>
<connect gate="PART_1" pin="3.3v@1" pad="20"/>
<connect gate="PART_1" pin="BAT" pad="21"/>
<connect gate="PART_1" pin="C13" pad="22"/>
<connect gate="PART_1" pin="C14" pad="23"/>
<connect gate="PART_1" pin="C15" pad="24"/>
<connect gate="PART_1" pin="A0" pad="25"/>
<connect gate="PART_1" pin="A1" pad="26"/>
<connect gate="PART_1" pin="A2" pad="27"/>
<connect gate="PART_1" pin="A3" pad="28"/>
<connect gate="PART_1" pin="A4" pad="29"/>
<connect gate="PART_1" pin="A5" pad="30"/>
<connect gate="PART_1" pin="A6" pad="31"/>
<connect gate="PART_1" pin="A7" pad="32"/>
<connect gate="PART_1" pin="B0" pad="33"/>
<connect gate="PART_1" pin="B1" pad="34"/>
<connect gate="PART_1" pin="B2" pad="35"/>
<connect gate="PART_1" pin="B10" pad="36"/>
<connect gate="PART_1" pin="B11" pad="37"/>
<connect gate="PART_1" pin="R" pad="38"/>
<connect gate="PART_1" pin="3.3v@2" pad="39"/>
<connect gate="PART_1" pin="G@2" pad="40"/>
</connects>
<technologies>
<technology name="">
<attribute name="VALUE" value="Pill STM32G431"/>
</technology>
</technologies>
</device>
</devices>
</deviceset>
<deviceset name="+19V" prefix="NetPort">
<gates>
<gate name="PART_1" symbol="+19V" x="0" y="0"/>
</gates>
<devices>
<device name="">
<connects/>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
</devicesets>
</library>
</libraries>
<classes>
<class number="0" name="Default" width="0" drill="0"/>
</classes>
<parts>
<part name="BLDC" library="common" deviceset="PLS_5" device="" value="BLDC  SHIELD"/>
<part name="C1" library="common" deviceset="CAP_P_5MM" device="" value="1000 mf"/>
<part name="C2" library="common" deviceset="CAP_0805_1206" device=""/>
<part name="C3" library="common" deviceset="CAP_P_3MM" device=""/>
<part name="C4" library="common" deviceset="CAP_P_3MM" device=""/>
<part name="C5" library="common" deviceset="CAP_0805_1206" device=""/>
<part name="C6" library="common" deviceset="CAP_SMD_P_5MM" device=""/>
<part name="C7" library="common" deviceset="CAP_SMD_P_5MM" device=""/>
<part name="C8" library="common" deviceset="CAP_0805_1206" device=""/>
<part name="C9" library="common" deviceset="CAP_0805_1206" device=""/>
<part name="C10" library="common" deviceset="CAP_P_5MM" device=""/>
<part name="C11" library="common" deviceset="CAP_P_5MM" device=""/>
<part name="DB25" library="common" deviceset="DB25M" device="" value="DB25M"/>
<part name="DC" library="common" deviceset="2_SCREW_TERM._BLK." device="" value="DC"/>
<part name="DCIN" library="common" deviceset="J-1" device="" value="DC IN"/>
<part name="ENCKP" library="common" deviceset="PLS_3" device="" value="ENCKP"/>
<part name="ENCSW" library="common" deviceset="PLS_3" device="" value="ENC SW"/>
<part name="FPC" library="common" deviceset="FPC_24_1MM" device="" value="FPC 24 1mm"/>
<part name="IC1" library="common" deviceset="FE1.1S" device="" value="FE1.1S"/>
<part name="J1" library="common" deviceset="USB-1_TYPE_A" device="" value="USB Type A"/>
<part name="LAZERKP" library="common" deviceset="PLS_3" device="" value="LAZER"/>
<part name="LAZERSW" library="common" deviceset="PLS_3" device="" value="LAZER SW"/>
<part name="NetPort1" library="common" deviceset="+19V" device=""/>
<part name="NetPort2" library="common" deviceset="+5V" device=""/>
<part name="NetPort3" library="common" deviceset="GND" device=""/>
<part name="NetPort4" library="common" deviceset="+5V" device=""/>
<part name="NetPort5" library="common" deviceset="GND" device=""/>
<part name="NetPort6" library="common" deviceset="GND" device=""/>
<part name="NetPort7" library="common" deviceset="+5V" device=""/>
<part name="NetPort8" library="common" deviceset="GND" device=""/>
<part name="NetPort9" library="common" deviceset="GND" device=""/>
<part name="NetPort10" library="common" deviceset="+19V" device=""/>
<part name="NetPort11" library="common" deviceset="GND" device=""/>
<part name="NetPort12" library="common" deviceset="+5V" device=""/>
<part name="NetPort13" library="common" deviceset="+19V" device=""/>
<part name="NetPort14" library="common" deviceset="+5V" device=""/>
<part name="NetPort15" library="common" deviceset="+5V" device=""/>
<part name="NetPort16" library="common" deviceset="+19V" device=""/>
<part name="NetPort17" library="common" deviceset="GND" device=""/>
<part name="NetPort18" library="common" deviceset="GND" device=""/>
<part name="NetPort19" library="common" deviceset="GND" device=""/>
<part name="NetPort20" library="common" deviceset="+5V" device=""/>
<part name="NetPort21" library="common" deviceset="+5V" device=""/>
<part name="NetPort22" library="common" deviceset="GND" device=""/>
<part name="R1" library="common" deviceset="R_0805_1206" device=""/>
<part name="R2" library="common" deviceset="R_0805_1206" device=""/>
<part name="R3" library="common" deviceset="R_0805_1206" device=""/>
<part name="R4" library="common" deviceset="R_0805_1206" device=""/>
<part name="R5" library="common" deviceset="R_0805_1206" device=""/>
<part name="R6" library="common" deviceset="R_0805_1206" device=""/>
<part name="R7" library="common" deviceset="R_0805_1206" device=""/>
<part name="R8" library="common" deviceset="R_0805_1206" device=""/>
<part name="R9" library="common" deviceset="R_0805_1206" device=""/>
<part name="R10" library="common" deviceset="R_0805_1206" device=""/>
<part name="R11" library="common" deviceset="R_0805_1206" device=""/>
<part name="R12" library="common" deviceset="R_0805_1206" device=""/>
<part name="R13" library="common" deviceset="R_0805_1206" device=""/>
<part name="R14" library="common" deviceset="R_0805_1206" device=""/>
<part name="STEPPERSHIELD" library="common" deviceset="PLS_16" device="" value="STEPPER SHIELD"/>
<part name="U1" library="common" deviceset="MAX15070AAUT+T" device="" value="MAX15070"/>
<part name="U3" library="common" deviceset="IFX007T" device="" value="IFX007T"/>
<part name="U4" library="common" deviceset="MAX15070AAUT+T" device="" value="MAX15070"/>
<part name="U5" library="common" deviceset="IFX007T" device="" value="IFX007T"/>
<part name="U7" library="common" deviceset="PILL_STM32G431" device="" value="Pill STM32G431"/>
<part name="U8" library="common" deviceset="BLUE_PILL_STM32F103" device="" value="Blue Pill STM32F103"/>
<part name="USB_IN" library="common" deviceset="USB-1_TYPE_B" device="" value="Type B, Receptacle"/>
<part name="USBPULLUP" library="common" deviceset="PLS_2" device="" value="USB PULLUP"/>
<part name="XP2" library="common" deviceset="PLS_2" device="" value="BKL SEL"/>
<part name="XP3" library="common" deviceset="PLS_2" device="" value="BKL  SEL"/>
<part name="Z" library="common" deviceset="Q_1" device=""/>
</parts>
<modules/>
<sheets>
<sheet>
<description>Лист1</description>
<plain>
<text x="113.824" y="-276.889" size="1.48" layer="97" font="vector" ratio="10" rot="R0" align="top-left" distance="77">GND
GND
GND
GND
GND
GND
GND
GND
Z ENABLE
-
PROBE
-
E_STOP
-
-
-
Z DIR
Z STEP
Y ENABLE
Y DIR
Y STEP
X ENABLE
X DIR
X STEP
-</text>
<text x="-0.476" y="-187.989" size="1.48" layer="97" font="vector" ratio="10" rot="R0" align="top-left" distance="77">+19
PWM
DIR
ENA
GND</text>
<text x="-104.934" y="-317.471" size="1.48" layer="97" font="vector" ratio="10" rot="R0" align="top-left" distance="77">USB_+5V
USB_+5V
USB_+5V
USB_DM
USB_DP
USB_GND
USB_GND
USB_GND
PWM_BKL
ENC_B
ENC_VCC
ENC_A
ENC_GND
SHIELD_GND
SHIELD_GND
SHIELD_GND
SHIELD_GND
PWM_LASER
POWER_GND
POWER_GND
POWER_GND
LASER_+19V
LASER_+19V
LASER_+19V</text>
<text x="54.451" y="-377.219" size="1.48" layer="97" font="vector" ratio="10" rot="R0" align="top-left" distance="77">PA2
LAZER
PA0</text>
<text x="135.414" y="-238.789" size="1.48" layer="97" font="vector" ratio="10" rot="R0" align="top-left" distance="77">PWM_LED
PWM_LASER
GND</text>
<text x="137.954" y="-204.499" size="1.48" layer="97" font="vector" ratio="10" rot="R0" align="top-left" distance="77">N OUT
P OUT</text>
<text x="135.414" y="-214.659" size="1.48" layer="97" font="vector" ratio="10" rot="R0" align="top-left" distance="77">OUT
OUT</text>
<text x="-56.039" y="-377.219" size="1.48" layer="97" font="vector" ratio="10" rot="R0" align="top-left" distance="77">PB5
X_ENC_B
PВ8</text>
<text x="-1.746" y="-344.199" size="1.48" layer="97" font="vector" ratio="10" rot="R0" align="top-left" distance="77">X2_EN
X_MO_R 
X_MO_L 
X_MO_ENA
USB_EN
Z_STEP
Z_DIR
USB_DM
USB_DP
-
-
-
-
X_ENC_A
PROBE
X_ENC_B
E_STOP
5V
GND
3.3V</text>
<text x="13.494" y="-344.199" size="1.48" layer="97" font="vector" ratio="10" rot="R0" align="top-left" distance="77">-
-
-
-
X2_DIR
X2_STEP
Y_DIR
Y_STEP
Y_EN
Z_EN
-
REZERV
REZERV
REZERV
PWM_LED
PWM_LASER
PC15
PC14
-
VBAT</text>
<text x="-1.746" y="-285.779" size="1.48" layer="97" font="vector" ratio="10" rot="R0" align="top-left" distance="77">-
-
-
-
ENC_A
ENC_B
-
USB_DM
USB_DP
Y_EN
MOS_LO_R
Y_DIR
MOS_LO_L
MOS_HO_R
Y_STEP
-
MOS_HO_L
5V
GND
3.3V</text>
<text x="13.494" y="-285.779" size="1.48" layer="97" font="vector" ratio="10" rot="R0" align="top-left" distance="77">-
-
-
-
-
-
-
-
-
-
-
-
REZERV
REZERV
REZERV
PWM_LASER
-
-
-
-</text>
<text x="106.204" y="-356.899" size="1.48" layer="97" font="vector" ratio="10" rot="R0" align="top-left" distance="77">+18V
+5V
X_STEP
X_DIR
X_ENABLE
Y_STEP
Y_DIR
Y_ENABLE
Z_STEP
Z_DIR
Z_ENABLE
E_STOP
PROBE
PWM_LED
PWM_LASER
GND</text>
<text x="-58.579" y="-285.779" size="1.48" layer="97" font="vector" ratio="10" rot="R0" align="top-left" distance="77">PA8
USB_DP</text>
<text x="-56.039" y="-363.249" size="1.48" layer="97" font="vector" ratio="10" rot="R0" align="top-left" distance="77">X_ENC_A
X_ENC_B
GND</text>
<text x="-9.316" y="-186.69" size="1.48" layer="97" font="vector" ratio="10" rot="R0" align="bottom-left" distance="76">BLDC  SHIELD</text>
<text x="24.759" y="-194.743" size="1.48" layer="97" font="vector" ratio="10" rot="R90" align="bottom-left" distance="76">1000 mf</text>
<text x="-61.995" y="-206.375" size="1.48" layer="97" font="vector" ratio="10" rot="R0" align="bottom-left" distance="76"></text>
<text x="-62.478" y="-211.449" size="1.48" layer="97" font="vector" ratio="10" rot="R0" align="bottom-left" distance="76"></text>
<text x="-62.478" y="-216.529" size="1.48" layer="97" font="vector" ratio="10" rot="R0" align="bottom-left" distance="76"></text>
<text x="-61.995" y="-221.615" size="1.48" layer="97" font="vector" ratio="10" rot="R0" align="bottom-left" distance="76"></text>
<text x="-142.488" y="-343.529" size="1.48" layer="97" font="vector" ratio="10" rot="R0" align="bottom-left" distance="76"></text>
<text x="-142.488" y="-348.609" size="1.48" layer="97" font="vector" ratio="10" rot="R0" align="bottom-left" distance="76"></text>
<text x="-142.005" y="-333.375" size="1.48" layer="97" font="vector" ratio="10" rot="R0" align="bottom-left" distance="76"></text>
<text x="-142.005" y="-328.295" size="1.48" layer="97" font="vector" ratio="10" rot="R0" align="bottom-left" distance="76"></text>
<text x="-142.488" y="-338.449" size="1.48" layer="97" font="vector" ratio="10" rot="R0" align="bottom-left" distance="76"></text>
<text x="-142.488" y="-353.689" size="1.48" layer="97" font="vector" ratio="10" rot="R0" align="bottom-left" distance="76"></text>
<text x="112.554" y="-278.656" size="1.233" layer="97" font="vector" ratio="10" rot="R180" align="top-left" distance="84">GND</text>
<text x="104.384" y="-274.955" size="1.48" layer="97" font="vector" ratio="10" rot="R0" align="bottom-left" distance="76">DB25M</text>
<text x="30.458" y="-224.79" size="1.48" layer="97" font="vector" ratio="10" rot="R0" align="bottom-left" distance="76">DC</text>
<text x="-151.604" y="-378.46" size="1.48" layer="97" font="vector" ratio="10" rot="R0" align="bottom-left" distance="76">DC IN</text>
<text x="-47.308" y="-363.22" size="1.48" layer="97" font="vector" ratio="10" rot="R0" align="bottom-left" distance="76">ENCKP</text>
<text x="-48.267" y="-377.19" size="1.48" layer="97" font="vector" ratio="10" rot="R0" align="bottom-left" distance="76">ENC SW</text>
<text x="-96.405" y="-346.71" size="1.48" layer="97" font="vector" ratio="10" rot="R0" align="bottom-left" distance="76">FPC 24 1mm</text>
<text x="-107.213" y="-198.12" size="1.48" layer="97" font="vector" ratio="10" rot="R0" align="bottom-left" distance="76">FE1.1S</text>
<text x="-149.343" y="-246.38" size="1.48" layer="97" font="vector" ratio="10" rot="R0" align="bottom-left" distance="76">USB Type A</text>
<text x="133.069" y="-238.76" size="1.48" layer="97" font="vector" ratio="10" rot="R0" align="bottom-left" distance="76">LAZER</text>
<text x="49.338" y="-377.19" size="1.48" layer="97" font="vector" ratio="10" rot="R0" align="bottom-left" distance="76">LAZER SW</text>
<text x="17.718" y="-176.3" size="1.48" layer="97" font="vector" ratio="10" rot="R0" align="bottom-left" distance="76">+19V</text>
<text x="105.73" y="-190.27" size="1.48" layer="97" font="vector" ratio="10" rot="R0" align="bottom-left" distance="76">+5V</text>
<text x="-81.915" y="-198.634" size="1.48" layer="97" font="vector" ratio="10" rot="R90" align="bottom-left" distance="76">GND</text>
<text x="-50.48" y="-223.29" size="1.48" layer="97" font="vector" ratio="10" rot="R0" align="bottom-left" distance="76">+5V</text>
<text x="-154.438" y="-234.974" size="1.48" layer="97" font="vector" ratio="10" rot="R0" align="bottom-left" distance="76">GND</text>
<text x="112.395" y="-263.404" size="1.48" layer="97" font="vector" ratio="10" rot="R90" align="bottom-left" distance="76">GND</text>
<text x="-154.94" y="-270.19" size="1.48" layer="97" font="vector" ratio="10" rot="R90" align="bottom-left" distance="76">+5V</text>
<text x="-55.245" y="-267.214" size="1.48" layer="97" font="vector" ratio="10" rot="R90" align="bottom-left" distance="76">GND</text>
<text x="20.955" y="-278.644" size="1.48" layer="97" font="vector" ratio="10" rot="R90" align="bottom-left" distance="76">GND</text>
<text x="-136.904" y="-374.42" size="1.48" layer="97" font="vector" ratio="10" rot="R0" align="bottom-left" distance="76">+19V</text>
<text x="-136.525" y="-398.024" size="1.48" layer="97" font="vector" ratio="10" rot="R90" align="bottom-left" distance="76">GND</text>
<text x="-61.91" y="-323.62" size="1.48" layer="97" font="vector" ratio="10" rot="R0" align="bottom-left" distance="76">+5V</text>
<text x="104.078" y="-343.94" size="1.48" layer="97" font="vector" ratio="10" rot="R0" align="bottom-left" distance="76">+19V</text>
<text x="115.89" y="-343.94" size="1.48" layer="97" font="vector" ratio="10" rot="R0" align="bottom-left" distance="76">+5V</text>
<text x="-70.8" y="-383.31" size="1.48" layer="97" font="vector" ratio="10" rot="R0" align="bottom-left" distance="76">+5V</text>
<text x="-71.182" y="-371.88" size="1.48" layer="97" font="vector" ratio="10" rot="R0" align="bottom-left" distance="76">+19V</text>
<text x="-70.485" y="-398.024" size="1.48" layer="97" font="vector" ratio="10" rot="R90" align="bottom-left" distance="76">GND</text>
<text x="93.345" y="-404.374" size="1.48" layer="97" font="vector" ratio="10" rot="R90" align="bottom-left" distance="76">GND</text>
<text x="-80.645" y="-398.024" size="1.48" layer="97" font="vector" ratio="10" rot="R90" align="bottom-left" distance="76">GND</text>
<text x="53.66" y="-289.33" size="1.48" layer="97" font="vector" ratio="10" rot="R0" align="bottom-left" distance="76">+5V</text>
<text x="-152.08" y="-322.35" size="1.48" layer="97" font="vector" ratio="10" rot="R0" align="bottom-left" distance="76">+5V</text>
<text x="-136.525" y="-365.004" size="1.48" layer="97" font="vector" ratio="10" rot="R90" align="bottom-left" distance="76">GND</text>
<text x="-131.845" y="-196.85" size="1.48" layer="97" font="vector" ratio="10" rot="R0" align="bottom-left" distance="76"></text>
<text x="54.845" y="-204.47" size="1.48" layer="97" font="vector" ratio="10" rot="R0" align="bottom-left" distance="76"></text>
<text x="-27.705" y="-219.71" size="1.48" layer="97" font="vector" ratio="10" rot="R0" align="bottom-left" distance="76"></text>
<text x="125.73" y="-225.825" size="1.48" layer="97" font="vector" ratio="10" rot="R90" align="bottom-left" distance="76"></text>
<text x="-27.705" y="-224.79" size="1.48" layer="97" font="vector" ratio="10" rot="R0" align="bottom-left" distance="76"></text>
<text x="-27.705" y="-236.22" size="1.48" layer="97" font="vector" ratio="10" rot="R0" align="bottom-left" distance="76"></text>
<text x="54.845" y="-238.76" size="1.48" layer="97" font="vector" ratio="10" rot="R0" align="bottom-left" distance="76"></text>
<text x="-27.705" y="-247.65" size="1.48" layer="97" font="vector" ratio="10" rot="R0" align="bottom-left" distance="76"></text>
<text x="-27.705" y="-252.73" size="1.48" layer="97" font="vector" ratio="10" rot="R0" align="bottom-left" distance="76"></text>
<text x="-28.975" y="-285.75" size="1.48" layer="97" font="vector" ratio="10" rot="R0" align="bottom-left" distance="76"></text>
<text x="63.735" y="-302.26" size="1.48" layer="97" font="vector" ratio="10" rot="R0" align="bottom-left" distance="76"></text>
<text x="63.735" y="-307.34" size="1.48" layer="97" font="vector" ratio="10" rot="R0" align="bottom-left" distance="76"></text>
<text x="-39.135" y="-314.96" size="1.48" layer="97" font="vector" ratio="10" rot="R0" align="bottom-left" distance="76"></text>
<text x="-39.135" y="-320.04" size="1.48" layer="97" font="vector" ratio="10" rot="R0" align="bottom-left" distance="76"></text>
<text x="95.905" y="-337.82" size="1.48" layer="97" font="vector" ratio="10" rot="R0" align="bottom-left" distance="76">STEPPER SHIELD</text>
<text x="83.351" y="-198.12" size="1.48" layer="97" font="vector" ratio="10" rot="R0" align="bottom-left" distance="76">MAX15070</text>
<text x="-0.628" y="-213.36" size="1.48" layer="97" font="vector" ratio="10" rot="R0" align="bottom-left" distance="76">IFX007T</text>
<text x="83.351" y="-232.41" size="1.48" layer="97" font="vector" ratio="10" rot="R0" align="bottom-left" distance="76">MAX15070</text>
<text x="-0.628" y="-241.3" size="1.48" layer="97" font="vector" ratio="10" rot="R0" align="bottom-left" distance="76">IFX007T</text>
<text x="4.163" y="-285.717" size="1.48" layer="97" font="vector" ratio="10" rot="R0" align="bottom-left" distance="76">Pill STM32G431</text>
<text x="1.241" y="-344.137" size="1.48" layer="97" font="vector" ratio="10" rot="R0" align="bottom-left" distance="76">Blue Pill STM32F103</text>
<text x="-74.819" y="-243.84" size="1.48" layer="97" font="vector" ratio="10" rot="R0" align="bottom-left" distance="76">Type B, Receptacle</text>
<text x="-57.235" y="-285.75" size="1.48" layer="97" font="vector" ratio="10" rot="R0" align="bottom-left" distance="76">USB PULLUP</text>
<text x="135.539" y="-204.47" size="1.48" layer="97" font="vector" ratio="10" rot="R0" align="bottom-left" distance="76">BKL SEL</text>
<text x="134.798" y="-214.63" size="1.48" layer="97" font="vector" ratio="10" rot="R0" align="bottom-left" distance="76">BKL  SEL</text>
<text x="-81.045" y="-206.502" size="1.48" layer="97" font="vector" ratio="10" rot="R0" align="bottom-left" distance="76"></text>
</plain>
<moduleinsts/>
<instances>
<instance part="BLDC" gate="PART_1" x="-1.27" y="-193.04" smashed="yes"/>
<instance part="C1" gate="PART_1" x="26.67" y="-190.017" rot="R270.000631377677" smashed="yes"/>
<instance part="C2" gate="PART_1" x="-62.23" y="-208.28" smashed="yes"/>
<instance part="C3" gate="PART_1" x="-62.713" y="-213.36" smashed="yes"/>
<instance part="C4" gate="PART_1" x="-62.713" y="-218.44" smashed="yes"/>
<instance part="C5" gate="PART_1" x="-62.23" y="-223.52" smashed="yes"/>
<instance part="C6" gate="PART_1" x="-142.723" y="-345.44" smashed="yes"/>
<instance part="C7" gate="PART_1" x="-142.723" y="-350.52" smashed="yes"/>
<instance part="C8" gate="PART_1" x="-142.24" y="-335.28" smashed="yes"/>
<instance part="C9" gate="PART_1" x="-142.24" y="-330.2" smashed="yes"/>
<instance part="C10" gate="PART_1" x="-142.723" y="-340.36" smashed="yes"/>
<instance part="C11" gate="PART_1" x="-142.723" y="-355.6" smashed="yes"/>
<instance part="DB25" gate="PART_1" x="107.95" y="-308.61" rot="R180.000420918452" smashed="yes"/>
<instance part="DC" gate="PART_1" x="31.75" y="-228.6" smashed="yes"/>
<instance part="DCIN" gate="PART_1" x="-148.59" y="-384.81" smashed="yes"/>
<instance part="ENCKP" gate="PART_1" x="-43.815" y="-367.03" rot="R180.000420918452" smashed="yes"/>
<instance part="ENCSW" gate="PART_1" x="-43.815" y="-381" rot="R180.000420918452" smashed="yes"/>
<instance part="FPC" gate="PART_1" x="-88.9" y="-377.19" rot="R180.000420918452" smashed="yes"/>
<instance part="IC1" gate="PART_1" x="-104.14" y="-231.14" rot="R180.000420918452" smashed="yes"/>
<instance part="J1" gate="PART_1" x="-142.24" y="-254" rot="R180.000420918452" smashed="yes"/>
<instance part="LAZERKP" gate="PART_1" x="136.525" y="-242.57" smashed="yes"/>
<instance part="LAZERSW" gate="PART_1" x="55.245" y="-381" smashed="yes"/>
<instance part="NetPort1" gate="PART_1" x="20.32" y="-177.8" smashed="yes"/>
<instance part="NetPort2" gate="PART_1" x="107.95" y="-191.77" smashed="yes"/>
<instance part="NetPort3" gate="PART_1" x="-80.01" y="-196.596" smashed="yes"/>
<instance part="NetPort4" gate="PART_1" x="-48.26" y="-224.79" smashed="yes"/>
<instance part="NetPort5" gate="PART_1" x="-152.4" y="-236.474" rot="R180.000420918452" smashed="yes"/>
<instance part="NetPort6" gate="PART_1" x="114.3" y="-261.366" smashed="yes"/>
<instance part="NetPort7" gate="PART_1" x="-152.4" y="-267.97" rot="R180.000420918452" smashed="yes"/>
<instance part="NetPort8" gate="PART_1" x="-53.34" y="-265.176" smashed="yes"/>
<instance part="NetPort9" gate="PART_1" x="22.86" y="-276.606" smashed="yes"/>
<instance part="NetPort10" gate="PART_1" x="-134.303" y="-375.92" smashed="yes"/>
<instance part="NetPort11" gate="PART_1" x="-134.62" y="-395.986" smashed="yes"/>
<instance part="NetPort12" gate="PART_1" x="-59.69" y="-325.12" smashed="yes"/>
<instance part="NetPort13" gate="PART_1" x="106.68" y="-345.44" smashed="yes"/>
<instance part="NetPort14" gate="PART_1" x="118.11" y="-345.44" smashed="yes"/>
<instance part="NetPort15" gate="PART_1" x="-68.58" y="-384.81" smashed="yes"/>
<instance part="NetPort16" gate="PART_1" x="-68.58" y="-373.38" smashed="yes"/>
<instance part="NetPort17" gate="PART_1" x="-68.58" y="-395.986" smashed="yes"/>
<instance part="NetPort18" gate="PART_1" x="95.25" y="-402.336" smashed="yes"/>
<instance part="NetPort19" gate="PART_1" x="-78.74" y="-395.986" smashed="yes"/>
<instance part="NetPort20" gate="PART_1" x="55.88" y="-290.83" smashed="yes"/>
<instance part="NetPort21" gate="PART_1" x="-149.86" y="-323.85" smashed="yes"/>
<instance part="NetPort22" gate="PART_1" x="-134.62" y="-362.966" smashed="yes"/>
<instance part="R1" gate="PART_1" x="-132.08" y="-198.12" smashed="yes"/>
<instance part="R2" gate="PART_1" x="54.61" y="-205.74" smashed="yes"/>
<instance part="R3" gate="PART_1" x="-27.94" y="-220.98" smashed="yes"/>
<instance part="R4" gate="PART_1" x="127" y="-226.06" rot="R270.000631377677" smashed="yes"/>
<instance part="R5" gate="PART_1" x="-27.94" y="-226.06" smashed="yes"/>
<instance part="R6" gate="PART_1" x="-27.94" y="-237.49" smashed="yes"/>
<instance part="R7" gate="PART_1" x="54.61" y="-240.03" smashed="yes"/>
<instance part="R8" gate="PART_1" x="-27.94" y="-248.92" smashed="yes"/>
<instance part="R9" gate="PART_1" x="-27.94" y="-254" smashed="yes"/>
<instance part="R10" gate="PART_1" x="-29.21" y="-287.02" smashed="yes"/>
<instance part="R11" gate="PART_1" x="63.5" y="-303.53" smashed="yes"/>
<instance part="R12" gate="PART_1" x="63.5" y="-308.61" smashed="yes"/>
<instance part="R13" gate="PART_1" x="-39.37" y="-316.23" smashed="yes"/>
<instance part="R14" gate="PART_1" x="-39.37" y="-321.31" smashed="yes"/>
<instance part="STEPPERSHIELD" gate="PART_1" x="105.41" y="-358.14" smashed="yes"/>
<instance part="U1" gate="PART_1" x="88.9" y="-208.28" smashed="yes"/>
<instance part="U3" gate="PART_1" x="3.81" y="-223.52" smashed="yes"/>
<instance part="U4" gate="PART_1" x="88.9" y="-242.57" smashed="yes"/>
<instance part="U5" gate="PART_1" x="3.81" y="-251.46" smashed="yes"/>
<instance part="U7" gate="PART_1" x="12.722" y="-311.126" smashed="yes"/>
<instance part="U8" gate="PART_1" x="12.722" y="-369.546" smashed="yes"/>
<instance part="USB_IN" gate="PART_1" x="-63.5" y="-251.46" smashed="yes"/>
<instance part="USBPULLUP" gate="PART_1" x="-50.165" y="-288.29" rot="R180.000420918452" smashed="yes"/>
<instance part="XP2" gate="PART_1" x="140.335" y="-207.01" smashed="yes"/>
<instance part="XP3" gate="PART_1" x="140.335" y="-217.17" smashed="yes"/>
<instance part="Z" gate="PART_1" x="-81.28" y="-208.28" smashed="yes"/>
</instances>
<busses/>
<nets>
<net name="Сеть_0" class="0">
<segment>
<wire layer="91" width="0.1" x1="-137.16" y1="-389.89" x2="-134.62" y2="-389.89"/>
<wire layer="91" width="0.1" x1="-134.62" y1="-389.89" x2="-134.62" y2="-392.43"/>
<pinref part="DCIN" gate="PART_1" pin="2"/>
<pinref part="NetPort11" gate="PART_1" pin="GND"/>
</segment>
<segment>
<wire layer="91" width="0.1" x1="-152.4" y1="-254" x2="-151.13" y2="-254"/>
<wire layer="91" width="0.1" x1="-152.4" y1="-254" x2="-152.4" y2="-248.92"/>
<wire layer="91" width="0.1" x1="-152.4" y1="-248.92" x2="-152.4" y2="-240.03"/>
<pinref part="J1" gate="PART_1" pin="GND"/>
<pinref part="NetPort5" gate="PART_1" pin="GND"/>
<wire layer="91" width="0.1" x1="-151.13" y1="-248.92" x2="-152.4" y2="-248.92"/>
<pinref part="J1" gate="PART_1" pin="CASE"/>
<junction x="-152.4" y="-248.92"/>
</segment>
<segment>
<wire layer="91" width="0.1" x1="-53.34" y1="-251.46" x2="-54.61" y2="-251.46"/>
<wire layer="91" width="0.1" x1="-53.34" y1="-256.54" x2="-53.34" y2="-261.62"/>
<wire layer="91" width="0.1" x1="-53.34" y1="-251.46" x2="-53.34" y2="-256.54"/>
<pinref part="USB_IN" gate="PART_1" pin="GND"/>
<pinref part="NetPort8" gate="PART_1" pin="GND"/>
<wire layer="91" width="0.1" x1="-54.61" y1="-256.54" x2="-53.34" y2="-256.54"/>
<pinref part="USB_IN" gate="PART_1" pin="CASE"/>
<junction x="-53.34" y="-256.54"/>
<wire layer="91" width="0.1" x1="-139.7" y1="-198.12" x2="-138.43" y2="-198.12"/>
<wire layer="91" width="0.1" x1="-139.7" y1="-198.12" x2="-139.7" y2="-186.69"/>
<wire layer="91" width="0.1" x1="-139.7" y1="-186.69" x2="-53.34" y2="-186.69"/>
<wire layer="91" width="0.1" x1="-53.34" y1="-223.52" x2="-53.34" y2="-251.46"/>
<wire layer="91" width="0.1" x1="-53.34" y1="-213.36" x2="-53.34" y2="-223.52"/>
<wire layer="91" width="0.1" x1="-53.34" y1="-186.69" x2="-53.34" y2="-213.36"/>
<pinref part="R1" gate="PART_1" pin="1"/>
<junction x="-53.34" y="-251.46"/>
<wire layer="91" width="0.1" x1="-57.15" y1="-223.52" x2="-53.34" y2="-223.52"/>
<junction x="-57.15" y="-223.52"/>
<wire layer="91" width="0.1" x1="-57.15" y1="-218.44" x2="-58.42" y2="-218.44"/>
<wire layer="91" width="0.1" x1="-57.15" y1="-223.52" x2="-58.42" y2="-223.52"/>
<wire layer="91" width="0.1" x1="-57.15" y1="-218.44" x2="-57.15" y2="-223.52"/>
<pinref part="C4" gate="PART_1" pin="MINUS"/>
<pinref part="C5" gate="PART_1" pin="2"/>
<junction x="-53.34" y="-223.52"/>
<wire layer="91" width="0.1" x1="-57.15" y1="-213.36" x2="-53.34" y2="-213.36"/>
<junction x="-57.15" y="-213.36"/>
<wire layer="91" width="0.1" x1="-57.15" y1="-208.28" x2="-58.42" y2="-208.28"/>
<wire layer="91" width="0.1" x1="-57.15" y1="-213.36" x2="-58.42" y2="-213.36"/>
<wire layer="91" width="0.1" x1="-57.15" y1="-208.28" x2="-57.15" y2="-213.36"/>
<pinref part="C2" gate="PART_1" pin="2"/>
<pinref part="C3" gate="PART_1" pin="MINUS"/>
<junction x="-53.34" y="-213.36"/>
</segment>
<segment>
<wire layer="91" width="0.1" x1="16.51" y1="-231.14" x2="22.86" y2="-231.14"/>
<wire layer="91" width="0.1" x1="22.86" y1="-231.14" x2="22.86" y2="-259.08"/>
<wire layer="91" width="0.1" x1="22.86" y1="-259.08" x2="16.51" y2="-259.08"/>
<pinref part="U3" gate="PART_1" pin="GND"/>
<pinref part="U5" gate="PART_1" pin="GND"/>
<wire layer="91" width="0.1" x1="22.86" y1="-259.08" x2="22.86" y2="-265.43"/>
<wire layer="91" width="0.1" x1="22.86" y1="-265.43" x2="22.86" y2="-273.05"/>
<pinref part="NetPort9" gate="PART_1" pin="GND"/>
<junction x="22.86" y="-259.08"/>
<wire layer="91" width="0.1" x1="-34.29" y1="-220.98" x2="-39.37" y2="-220.98"/>
<wire layer="91" width="0.1" x1="-39.37" y1="-254" x2="-39.37" y2="-265.43"/>
<wire layer="91" width="0.1" x1="-39.37" y1="-248.92" x2="-39.37" y2="-254"/>
<wire layer="91" width="0.1" x1="-39.37" y1="-237.49" x2="-39.37" y2="-248.92"/>
<wire layer="91" width="0.1" x1="-39.37" y1="-220.98" x2="-39.37" y2="-226.06"/>
<wire layer="91" width="0.1" x1="-39.37" y1="-226.06" x2="-39.37" y2="-220.98"/>
<wire layer="91" width="0.1" x1="-39.37" y1="-220.98" x2="-39.37" y2="-237.49"/>
<wire layer="91" width="0.1" x1="-39.37" y1="-265.43" x2="22.86" y2="-265.43"/>
<pinref part="R3" gate="PART_1" pin="1"/>
<junction x="22.86" y="-265.43"/>
<wire layer="91" width="0.1" x1="-34.29" y1="-226.06" x2="-39.37" y2="-226.06"/>
<pinref part="R5" gate="PART_1" pin="1"/>
<junction x="-39.37" y="-226.06"/>
<wire layer="91" width="0.1" x1="-34.29" y1="-237.49" x2="-39.37" y2="-237.49"/>
<pinref part="R6" gate="PART_1" pin="1"/>
<junction x="-39.37" y="-237.49"/>
<wire layer="91" width="0.1" x1="-34.29" y1="-248.92" x2="-39.37" y2="-248.92"/>
<pinref part="R8" gate="PART_1" pin="1"/>
<junction x="-39.37" y="-248.92"/>
<wire layer="91" width="0.1" x1="-34.29" y1="-254" x2="-39.37" y2="-254"/>
<pinref part="R9" gate="PART_1" pin="1"/>
<junction x="-39.37" y="-254"/>
<wire layer="91" width="0.1" x1="-7.62" y1="-199.39" x2="-39.37" y2="-199.39"/>
<wire layer="91" width="0.1" x1="-39.37" y1="-199.39" x2="-39.37" y2="-220.98"/>
<pinref part="BLDC" gate="PART_1" pin="5"/>
<junction x="-39.37" y="-220.98"/>
<wire layer="91" width="0.1" x1="26.67" y1="-195.58" x2="26.67" y2="-194.31"/>
<wire layer="91" width="0.1" x1="26.67" y1="-195.58" x2="22.86" y2="-195.58"/>
<wire layer="91" width="0.1" x1="22.86" y1="-195.58" x2="22.86" y2="-231.14"/>
<pinref part="C1" gate="PART_1" pin="MINUS"/>
<junction x="22.86" y="-231.14"/>
</segment>
<segment>
<wire layer="91" width="0.1" x1="104.14" y1="-213.36" x2="114.3" y2="-213.36"/>
<wire layer="91" width="0.1" x1="114.3" y1="-255.27" x2="114.3" y2="-257.81"/>
<wire layer="91" width="0.1" x1="114.3" y1="-247.65" x2="114.3" y2="-255.27"/>
<wire layer="91" width="0.1" x1="114.3" y1="-245.11" x2="114.3" y2="-247.65"/>
<wire layer="91" width="0.1" x1="114.3" y1="-213.36" x2="114.3" y2="-220.98"/>
<wire layer="91" width="0.1" x1="114.3" y1="-220.98" x2="114.3" y2="-245.11"/>
<pinref part="U1" gate="PART_1" pin="GND"/>
<pinref part="NetPort6" gate="PART_1" pin="GND"/>
<wire layer="91" width="0.1" x1="104.14" y1="-247.65" x2="114.3" y2="-247.65"/>
<pinref part="U4" gate="PART_1" pin="GND"/>
<junction x="114.3" y="-247.65"/>
<wire layer="91" width="0.1" x1="73.66" y1="-208.28" x2="69.85" y2="-208.28"/>
<wire layer="91" width="0.1" x1="69.85" y1="-208.28" x2="69.85" y2="-220.98"/>
<wire layer="91" width="0.1" x1="69.85" y1="-220.98" x2="114.3" y2="-220.98"/>
<pinref part="U1" gate="PART_1" pin="IN-"/>
<junction x="114.3" y="-220.98"/>
<wire layer="91" width="0.1" x1="73.66" y1="-242.57" x2="69.85" y2="-242.57"/>
<wire layer="91" width="0.1" x1="69.85" y1="-242.57" x2="69.85" y2="-255.27"/>
<wire layer="91" width="0.1" x1="69.85" y1="-255.27" x2="114.3" y2="-255.27"/>
<pinref part="U4" gate="PART_1" pin="IN-"/>
<junction x="114.3" y="-255.27"/>
<wire layer="91" width="0.1" x1="48.26" y1="-205.74" x2="44.45" y2="-205.74"/>
<wire layer="91" width="0.1" x1="44.45" y1="-240.03" x2="44.45" y2="-255.27"/>
<wire layer="91" width="0.1" x1="44.45" y1="-205.74" x2="44.45" y2="-240.03"/>
<wire layer="91" width="0.1" x1="44.45" y1="-255.27" x2="69.85" y2="-255.27"/>
<pinref part="R2" gate="PART_1" pin="1"/>
<junction x="69.85" y="-255.27"/>
<wire layer="91" width="0.1" x1="48.26" y1="-240.03" x2="44.45" y2="-240.03"/>
<pinref part="R7" gate="PART_1" pin="1"/>
<junction x="44.45" y="-240.03"/>
<wire layer="91" width="0.1" x1="128.27" y1="-245.11" x2="114.3" y2="-245.11"/>
<pinref part="LAZERKP" gate="PART_1" pin="3"/>
<junction x="114.3" y="-245.11"/>
</segment>
<segment>
<wire layer="91" width="0.1" x1="-91.44" y1="-198.12" x2="-87.63" y2="-198.12"/>
<wire layer="91" width="0.1" x1="-87.63" y1="-198.12" x2="-87.63" y2="-191.77"/>
<wire layer="91" width="0.1" x1="-80.01" y1="-191.77" x2="-80.01" y2="-193.04"/>
<wire layer="91" width="0.1" x1="-87.63" y1="-191.77" x2="-80.01" y2="-191.77"/>
<pinref part="IC1" gate="PART_1" pin="VSS"/>
<pinref part="NetPort3" gate="PART_1" pin="GND"/>
</segment>
<segment>
<wire layer="91" width="0.1" x1="-68.58" y1="-391.16" x2="-68.58" y2="-392.43"/>
<wire layer="91" width="0.1" x1="-10.16" y1="-391.16" x2="-31.75" y2="-391.16"/>
<wire layer="91" width="0.1" x1="-31.75" y1="-391.16" x2="-19.05" y2="-391.16"/>
<wire layer="91" width="0.1" x1="-19.05" y1="-391.16" x2="-68.58" y2="-391.16"/>
<pinref part="U8" gate="PART_1" pin="G@1"/>
<pinref part="NetPort17" gate="PART_1" pin="GND"/>
<wire layer="91" width="0.1" x1="-10.16" y1="-332.74" x2="-19.05" y2="-332.74"/>
<wire layer="91" width="0.1" x1="-19.05" y1="-332.74" x2="-19.05" y2="-391.16"/>
<pinref part="U7" gate="PART_1" pin="G@1"/>
<junction x="-19.05" y="-391.16"/>
<wire layer="91" width="0.1" x1="-35.56" y1="-369.57" x2="-31.75" y2="-369.57"/>
<wire layer="91" width="0.1" x1="-31.75" y1="-369.57" x2="-31.75" y2="-391.16"/>
<pinref part="ENCKP" gate="PART_1" pin="1"/>
<junction x="-31.75" y="-391.16"/>
</segment>
<segment>
<wire layer="91" width="0.1" x1="-82.55" y1="-369.57" x2="-78.74" y2="-369.57"/>
<wire layer="91" width="0.1" x1="-78.74" y1="-369.57" x2="-78.74" y2="-367.03"/>
<wire layer="91" width="0.1" x1="-78.74" y1="-367.03" x2="-82.55" y2="-367.03"/>
<pinref part="FPC" gate="PART_1" pin="4"/>
<pinref part="FPC" gate="PART_1" pin="5"/>
<wire layer="91" width="0.1" x1="-78.74" y1="-367.03" x2="-78.74" y2="-364.49"/>
<wire layer="91" width="0.1" x1="-78.74" y1="-364.49" x2="-82.55" y2="-364.49"/>
<pinref part="FPC" gate="PART_1" pin="6"/>
<junction x="-78.74" y="-367.03"/>
<wire layer="91" width="0.1" x1="-82.55" y1="-359.41" x2="-78.74" y2="-359.41"/>
<wire layer="91" width="0.1" x1="-78.74" y1="-359.41" x2="-78.74" y2="-364.49"/>
<pinref part="FPC" gate="PART_1" pin="8"/>
<junction x="-78.74" y="-364.49"/>
<wire layer="91" width="0.1" x1="-78.74" y1="-359.41" x2="-78.74" y2="-356.87"/>
<wire layer="91" width="0.1" x1="-78.74" y1="-356.87" x2="-82.55" y2="-356.87"/>
<pinref part="FPC" gate="PART_1" pin="9"/>
<junction x="-78.74" y="-359.41"/>
<wire layer="91" width="0.1" x1="-78.74" y1="-356.87" x2="-78.74" y2="-354.33"/>
<wire layer="91" width="0.1" x1="-78.74" y1="-354.33" x2="-82.55" y2="-354.33"/>
<pinref part="FPC" gate="PART_1" pin="10"/>
<junction x="-78.74" y="-356.87"/>
<wire layer="91" width="0.1" x1="-78.74" y1="-354.33" x2="-78.74" y2="-351.79"/>
<wire layer="91" width="0.1" x1="-78.74" y1="-351.79" x2="-82.55" y2="-351.79"/>
<pinref part="FPC" gate="PART_1" pin="11"/>
<junction x="-78.74" y="-354.33"/>
<wire layer="91" width="0.1" x1="-78.74" y1="-336.55" x2="-78.74" y2="-349.25"/>
<wire layer="91" width="0.1" x1="-78.74" y1="-351.79" x2="-78.74" y2="-336.55"/>
<wire layer="91" width="0.1" x1="-78.74" y1="-349.25" x2="-82.55" y2="-349.25"/>
<pinref part="FPC" gate="PART_1" pin="12"/>
<junction x="-78.74" y="-351.79"/>
<wire layer="91" width="0.1" x1="-78.74" y1="-336.55" x2="-78.74" y2="-349.25"/>
<junction x="-78.74" y="-336.55"/>
<wire layer="91" width="0.1" x1="-82.55" y1="-331.47" x2="-78.74" y2="-331.47"/>
<wire layer="91" width="0.1" x1="-78.74" y1="-334.01" x2="-78.74" y2="-336.55"/>
<wire layer="91" width="0.1" x1="-78.74" y1="-349.25" x2="-78.74" y2="-334.01"/>
<wire layer="91" width="0.1" x1="-78.74" y1="-331.47" x2="-78.74" y2="-349.25"/>
<wire layer="91" width="0.1" x1="-78.74" y1="-336.55" x2="-82.55" y2="-336.55"/>
<pinref part="FPC" gate="PART_1" pin="19"/>
<pinref part="FPC" gate="PART_1" pin="17"/>
<wire layer="91" width="0.1" x1="-82.55" y1="-334.01" x2="-78.74" y2="-334.01"/>
<pinref part="FPC" gate="PART_1" pin="18"/>
<junction x="-78.74" y="-334.01"/>
<junction x="-78.74" y="-349.25"/>
<wire layer="91" width="0.1" x1="-78.74" y1="-369.57" x2="-78.74" y2="-392.43"/>
<pinref part="NetPort19" gate="PART_1" pin="GND"/>
<junction x="-78.74" y="-369.57"/>
</segment>
<segment>
<wire layer="91" width="0.1" x1="100.33" y1="-278.13" x2="95.25" y2="-278.13"/>
<wire layer="91" width="0.1" x1="95.25" y1="-278.13" x2="95.25" y2="-280.67"/>
<wire layer="91" width="0.1" x1="95.25" y1="-280.67" x2="100.33" y2="-280.67"/>
<pinref part="DB25" gate="PART_1" pin="P25"/>
<pinref part="DB25" gate="PART_1" pin="P24"/>
<wire layer="91" width="0.1" x1="95.25" y1="-280.67" x2="95.25" y2="-283.21"/>
<wire layer="91" width="0.1" x1="95.25" y1="-283.21" x2="100.33" y2="-283.21"/>
<pinref part="DB25" gate="PART_1" pin="P23"/>
<junction x="95.25" y="-280.67"/>
<wire layer="91" width="0.1" x1="95.25" y1="-283.21" x2="95.25" y2="-285.75"/>
<wire layer="91" width="0.1" x1="95.25" y1="-285.75" x2="100.33" y2="-285.75"/>
<pinref part="DB25" gate="PART_1" pin="P22"/>
<junction x="95.25" y="-283.21"/>
<wire layer="91" width="0.1" x1="95.25" y1="-285.75" x2="95.25" y2="-288.29"/>
<wire layer="91" width="0.1" x1="95.25" y1="-288.29" x2="100.33" y2="-288.29"/>
<pinref part="DB25" gate="PART_1" pin="P21"/>
<junction x="95.25" y="-285.75"/>
<wire layer="91" width="0.1" x1="95.25" y1="-288.29" x2="95.25" y2="-290.83"/>
<wire layer="91" width="0.1" x1="95.25" y1="-290.83" x2="100.33" y2="-290.83"/>
<pinref part="DB25" gate="PART_1" pin="P20"/>
<junction x="95.25" y="-288.29"/>
<wire layer="91" width="0.1" x1="95.25" y1="-290.83" x2="95.25" y2="-293.37"/>
<wire layer="91" width="0.1" x1="95.25" y1="-293.37" x2="100.33" y2="-293.37"/>
<pinref part="DB25" gate="PART_1" pin="P19"/>
<junction x="95.25" y="-290.83"/>
<wire layer="91" width="0.1" x1="95.25" y1="-293.37" x2="95.25" y2="-295.91"/>
<wire layer="91" width="0.1" x1="95.25" y1="-295.91" x2="100.33" y2="-295.91"/>
<pinref part="DB25" gate="PART_1" pin="P18"/>
<junction x="95.25" y="-293.37"/>
<wire layer="91" width="0.1" x1="95.25" y1="-295.91" x2="95.25" y2="-396.24"/>
<wire layer="91" width="0.1" x1="95.25" y1="-396.24" x2="99.06" y2="-396.24"/>
<pinref part="STEPPERSHIELD" gate="PART_1" pin="16"/>
<junction x="95.25" y="-295.91"/>
<wire layer="91" width="0.1" x1="95.25" y1="-396.24" x2="95.25" y2="-398.78"/>
<pinref part="NetPort18" gate="PART_1" pin="GND"/>
<junction x="95.25" y="-396.24"/>
<wire layer="91" width="0.1" x1="100.33" y1="-275.59" x2="95.25" y2="-275.59"/>
<wire layer="91" width="0.1" x1="95.25" y1="-275.59" x2="95.25" y2="-278.13"/>
<pinref part="DB25" gate="PART_1" pin="GND"/>
<junction x="95.25" y="-278.13"/>
</segment>
<segment>
<wire layer="91" width="0.1" x1="-138.43" y1="-330.2" x2="-134.62" y2="-330.2"/>
<wire layer="91" width="0.1" x1="-134.62" y1="-330.2" x2="-134.62" y2="-335.28"/>
<wire layer="91" width="0.1" x1="-134.62" y1="-335.28" x2="-138.43" y2="-335.28"/>
<pinref part="C9" gate="PART_1" pin="2"/>
<pinref part="C8" gate="PART_1" pin="2"/>
<wire layer="91" width="0.1" x1="-134.62" y1="-335.28" x2="-134.62" y2="-340.36"/>
<wire layer="91" width="0.1" x1="-134.62" y1="-340.36" x2="-138.43" y2="-340.36"/>
<pinref part="C10" gate="PART_1" pin="MINUS"/>
<junction x="-134.62" y="-335.28"/>
<wire layer="91" width="0.1" x1="-134.62" y1="-340.36" x2="-134.62" y2="-345.44"/>
<wire layer="91" width="0.1" x1="-134.62" y1="-345.44" x2="-138.43" y2="-345.44"/>
<pinref part="C6" gate="PART_1" pin="MINUS"/>
<junction x="-134.62" y="-340.36"/>
<wire layer="91" width="0.1" x1="-134.62" y1="-345.44" x2="-134.62" y2="-350.52"/>
<wire layer="91" width="0.1" x1="-134.62" y1="-350.52" x2="-138.43" y2="-350.52"/>
<pinref part="C7" gate="PART_1" pin="MINUS"/>
<junction x="-134.62" y="-345.44"/>
<wire layer="91" width="0.1" x1="-134.62" y1="-350.52" x2="-134.62" y2="-355.6"/>
<wire layer="91" width="0.1" x1="-134.62" y1="-355.6" x2="-138.43" y2="-355.6"/>
<pinref part="C11" gate="PART_1" pin="MINUS"/>
<junction x="-134.62" y="-350.52"/>
<wire layer="91" width="0.1" x1="-134.62" y1="-355.6" x2="-134.62" y2="-359.41"/>
<pinref part="NetPort22" gate="PART_1" pin="GND"/>
<junction x="-134.62" y="-355.6"/>
</segment>
</net>
<net name="Сеть_1" class="0">
<segment>
<wire layer="91" width="0.1" x1="-91.44" y1="-205.74" x2="-88.9" y2="-205.74"/>
<wire layer="91" width="0.1" x1="-88.9" y1="-205.74" x2="-88.9" y2="-204.47"/>
<wire layer="91" width="0.1" x1="-88.9" y1="-204.47" x2="-76.2" y2="-204.47"/>
<wire layer="91" width="0.1" x1="-76.2" y1="-208.28" x2="-77.47" y2="-208.28"/>
<wire layer="91" width="0.1" x1="-76.2" y1="-204.47" x2="-76.2" y2="-208.28"/>
<pinref part="IC1" gate="PART_1" pin="XIN"/>
<pinref part="Z" gate="PART_1" pin="OSC2"/>
</segment>
</net>
<net name="Сеть_2" class="0">
<segment>
<wire layer="91" width="0.1" x1="-91.44" y1="-208.28" x2="-85.09" y2="-208.28"/>
<pinref part="IC1" gate="PART_1" pin="XOUT"/>
<pinref part="Z" gate="PART_1" pin="OSC1"/>
</segment>
</net>
<net name="Сеть_3" class="0">
<segment>
<wire layer="91" width="0.1" x1="16.51" y1="-220.98" x2="25.4" y2="-220.98"/>
<wire layer="91" width="0.1" x1="25.4" y1="-220.98" x2="25.4" y2="-226.06"/>
<wire layer="91" width="0.1" x1="25.4" y1="-226.06" x2="26.67" y2="-226.06"/>
<pinref part="U3" gate="PART_1" pin="OUT"/>
<pinref part="DC" gate="PART_1" pin="2"/>
</segment>
</net>
<net name="Сеть_4" class="0">
<segment>
<wire layer="91" width="0.1" x1="-21.59" y1="-287.02" x2="-22.86" y2="-287.02"/>
<wire layer="91" width="0.1" x1="-21.59" y1="-287.02" x2="-21.59" y2="-355.582"/>
<wire layer="91" width="0.1" x1="-21.59" y1="-355.582" x2="-10.16" y2="-355.582"/>
<pinref part="R10" gate="PART_1" pin="2"/>
<pinref part="U8" gate="PART_1" pin="A8"/>
</segment>
</net>
<net name="Сеть_5" class="0">
<segment>
<wire layer="91" width="0.1" x1="16.51" y1="-248.92" x2="25.4" y2="-248.92"/>
<wire layer="91" width="0.1" x1="25.4" y1="-248.92" x2="25.4" y2="-231.14"/>
<wire layer="91" width="0.1" x1="25.4" y1="-231.14" x2="26.67" y2="-231.14"/>
<pinref part="U5" gate="PART_1" pin="OUT"/>
<pinref part="DC" gate="PART_1" pin="1"/>
</segment>
</net>
<net name="Сеть_6" class="0">
<segment>
<wire layer="91" width="0.1" x1="-10.16" y1="-297.162" x2="-22.86" y2="-297.162"/>
<wire layer="91" width="0.1" x1="-22.86" y1="-367.03" x2="-22.86" y2="-378.46"/>
<wire layer="91" width="0.1" x1="-22.86" y1="-346.71" x2="-22.86" y2="-367.03"/>
<wire layer="91" width="0.1" x1="-22.86" y1="-297.162" x2="-22.86" y2="-346.71"/>
<wire layer="91" width="0.1" x1="-22.86" y1="-378.46" x2="-10.16" y2="-378.46"/>
<pinref part="U7" gate="PART_1" pin="A8"/>
<pinref part="U8" gate="PART_1" pin="B6"/>
<wire layer="91" width="0.1" x1="-22.86" y1="-346.71" x2="-82.55" y2="-346.71"/>
<pinref part="FPC" gate="PART_1" pin="13"/>
<junction x="-22.86" y="-346.71"/>
<wire layer="91" width="0.1" x1="-29.21" y1="-367.03" x2="-22.86" y2="-367.03"/>
<wire layer="91" width="0.1" x1="-35.56" y1="-367.03" x2="-29.21" y2="-367.03"/>
<pinref part="ENCKP" gate="PART_1" pin="2"/>
<junction x="-22.86" y="-367.03"/>
<wire layer="91" width="0.1" x1="-33.02" y1="-321.31" x2="-29.21" y2="-321.31"/>
<wire layer="91" width="0.1" x1="-29.21" y1="-321.31" x2="-29.21" y2="-367.03"/>
<pinref part="R14" gate="PART_1" pin="2"/>
<junction x="-29.21" y="-367.03"/>
</segment>
</net>
<net name="Сеть_7" class="0">
<segment>
<wire layer="91" width="0.1" x1="-152.4" y1="-259.08" x2="-151.13" y2="-259.08"/>
<wire layer="91" width="0.1" x1="-152.4" y1="-259.08" x2="-152.4" y2="-265.43"/>
<pinref part="J1" gate="PART_1" pin="VBUS"/>
<pinref part="NetPort7" gate="PART_1" pin="+5V"/>
</segment>
<segment>
<wire layer="91" width="0.1" x1="-48.26" y1="-227.33" x2="-48.26" y2="-228.6"/>
<wire layer="91" width="0.1" x1="-48.26" y1="-228.6" x2="-48.26" y2="-246.38"/>
<wire layer="91" width="0.1" x1="-48.26" y1="-246.38" x2="-54.61" y2="-246.38"/>
<pinref part="NetPort4" gate="PART_1" pin="+5V"/>
<pinref part="USB_IN" gate="PART_1" pin="VBUS"/>
<wire layer="91" width="0.1" x1="-91.44" y1="-228.6" x2="-48.26" y2="-228.6"/>
<pinref part="IC1" gate="PART_1" pin="VDD5"/>
<junction x="-48.26" y="-228.6"/>
</segment>
<segment>
<wire layer="91" width="0.1" x1="104.14" y1="-200.66" x2="107.95" y2="-200.66"/>
<wire layer="91" width="0.1" x1="107.95" y1="-200.66" x2="107.95" y2="-234.95"/>
<wire layer="91" width="0.1" x1="107.95" y1="-234.95" x2="104.14" y2="-234.95"/>
<pinref part="U1" gate="PART_1" pin="V+"/>
<pinref part="U4" gate="PART_1" pin="V+"/>
<wire layer="91" width="0.1" x1="107.95" y1="-194.31" x2="107.95" y2="-200.66"/>
<pinref part="NetPort2" gate="PART_1" pin="+5V"/>
<junction x="107.95" y="-200.66"/>
</segment>
<segment>
<wire layer="91" width="0.1" x1="-68.58" y1="-388.62" x2="-68.58" y2="-387.35"/>
<wire layer="91" width="0.1" x1="-20.32" y1="-388.62" x2="-10.16" y2="-388.62"/>
<wire layer="91" width="0.1" x1="-68.58" y1="-388.62" x2="-20.32" y2="-388.62"/>
<pinref part="NetPort15" gate="PART_1" pin="+5V"/>
<pinref part="U8" gate="PART_1" pin="5v"/>
<wire layer="91" width="0.1" x1="-10.16" y1="-330.2" x2="-20.32" y2="-330.2"/>
<wire layer="91" width="0.1" x1="-20.32" y1="-330.2" x2="-20.32" y2="-388.62"/>
<pinref part="U7" gate="PART_1" pin="5v"/>
<junction x="-20.32" y="-388.62"/>
</segment>
<segment>
<wire layer="91" width="0.1" x1="118.11" y1="-347.98" x2="118.11" y2="-353.06"/>
<wire layer="91" width="0.1" x1="118.11" y1="-353.06" x2="97.79" y2="-353.06"/>
<wire layer="91" width="0.1" x1="97.79" y1="-360.68" x2="99.06" y2="-360.68"/>
<wire layer="91" width="0.1" x1="97.79" y1="-353.06" x2="97.79" y2="-360.68"/>
<pinref part="NetPort14" gate="PART_1" pin="+5V"/>
<pinref part="STEPPERSHIELD" gate="PART_1" pin="2"/>
</segment>
<segment>
<wire layer="91" width="0.1" x1="-82.55" y1="-318.77" x2="-77.47" y2="-318.77"/>
<wire layer="91" width="0.1" x1="-77.47" y1="-321.31" x2="-77.47" y2="-323.85"/>
<wire layer="91" width="0.1" x1="-77.47" y1="-318.77" x2="-77.47" y2="-321.31"/>
<wire layer="91" width="0.1" x1="-77.47" y1="-323.85" x2="-82.55" y2="-323.85"/>
<pinref part="FPC" gate="PART_1" pin="24"/>
<pinref part="FPC" gate="PART_1" pin="22"/>
<wire layer="91" width="0.1" x1="-82.55" y1="-321.31" x2="-77.47" y2="-321.31"/>
<pinref part="FPC" gate="PART_1" pin="23"/>
<junction x="-77.47" y="-321.31"/>
<wire layer="91" width="0.1" x1="-77.47" y1="-323.85" x2="-77.47" y2="-331.47"/>
<wire layer="91" width="0.1" x1="-77.47" y1="-331.47" x2="-77.47" y2="-344.17"/>
<wire layer="91" width="0.1" x1="-77.47" y1="-344.17" x2="-82.55" y2="-344.17"/>
<pinref part="FPC" gate="PART_1" pin="14"/>
<junction x="-77.47" y="-323.85"/>
<wire layer="91" width="0.1" x1="-77.47" y1="-331.47" x2="-59.69" y2="-331.47"/>
<wire layer="91" width="0.1" x1="-59.69" y1="-331.47" x2="-59.69" y2="-327.66"/>
<pinref part="NetPort12" gate="PART_1" pin="+5V"/>
<junction x="-77.47" y="-331.47"/>
<wire layer="91" width="0.1" x1="-46.99" y1="-321.31" x2="-46.99" y2="-331.47"/>
<wire layer="91" width="0.1" x1="-46.99" y1="-331.47" x2="-59.69" y2="-331.47"/>
<junction x="-46.99" y="-321.31"/>
<wire layer="91" width="0.1" x1="-46.99" y1="-321.31" x2="-45.72" y2="-321.31"/>
<wire layer="91" width="0.1" x1="-46.99" y1="-316.23" x2="-45.72" y2="-316.23"/>
<wire layer="91" width="0.1" x1="-46.99" y1="-321.31" x2="-46.99" y2="-316.23"/>
<pinref part="R14" gate="PART_1" pin="1"/>
<pinref part="R13" gate="PART_1" pin="1"/>
<junction x="-59.69" y="-331.47"/>
</segment>
<segment>
<wire layer="91" width="0.1" x1="55.88" y1="-308.61" x2="57.15" y2="-308.61"/>
<wire layer="91" width="0.1" x1="55.88" y1="-303.53" x2="55.88" y2="-308.61"/>
<wire layer="91" width="0.1" x1="55.88" y1="-293.37" x2="55.88" y2="-303.53"/>
<pinref part="NetPort20" gate="PART_1" pin="+5V"/>
<pinref part="R12" gate="PART_1" pin="1"/>
<wire layer="91" width="0.1" x1="55.88" y1="-303.53" x2="57.15" y2="-303.53"/>
<pinref part="R11" gate="PART_1" pin="1"/>
<junction x="55.88" y="-303.53"/>
</segment>
<segment>
<wire layer="91" width="0.1" x1="-146.05" y1="-330.2" x2="-149.86" y2="-330.2"/>
<wire layer="91" width="0.1" x1="-149.86" y1="-330.2" x2="-149.86" y2="-335.28"/>
<wire layer="91" width="0.1" x1="-149.86" y1="-335.28" x2="-146.05" y2="-335.28"/>
<pinref part="C9" gate="PART_1" pin="1"/>
<pinref part="C8" gate="PART_1" pin="1"/>
<wire layer="91" width="0.1" x1="-149.86" y1="-335.28" x2="-149.86" y2="-340.36"/>
<wire layer="91" width="0.1" x1="-149.86" y1="-340.36" x2="-146.05" y2="-340.36"/>
<pinref part="C10" gate="PART_1" pin="PLUS"/>
<junction x="-149.86" y="-335.28"/>
<wire layer="91" width="0.1" x1="-149.86" y1="-340.36" x2="-149.86" y2="-345.44"/>
<wire layer="91" width="0.1" x1="-149.86" y1="-345.44" x2="-146.05" y2="-345.44"/>
<pinref part="C6" gate="PART_1" pin="PLUS"/>
<junction x="-149.86" y="-340.36"/>
<wire layer="91" width="0.1" x1="-149.86" y1="-345.44" x2="-149.86" y2="-350.52"/>
<wire layer="91" width="0.1" x1="-149.86" y1="-350.52" x2="-146.05" y2="-350.52"/>
<pinref part="C7" gate="PART_1" pin="PLUS"/>
<junction x="-149.86" y="-345.44"/>
<wire layer="91" width="0.1" x1="-149.86" y1="-350.52" x2="-149.86" y2="-355.6"/>
<wire layer="91" width="0.1" x1="-149.86" y1="-355.6" x2="-146.05" y2="-355.6"/>
<pinref part="C11" gate="PART_1" pin="PLUS"/>
<junction x="-149.86" y="-350.52"/>
<wire layer="91" width="0.1" x1="-149.86" y1="-326.39" x2="-149.86" y2="-330.2"/>
<pinref part="NetPort21" gate="PART_1" pin="+5V"/>
<junction x="-149.86" y="-330.2"/>
</segment>
</net>
<net name="Сеть_8" class="0">
<segment>
<wire layer="91" width="0.1" x1="-133.35" y1="-256.54" x2="-119.38" y2="-256.54"/>
<pinref part="J1" gate="PART_1" pin="D+"/>
<pinref part="IC1" gate="PART_1" pin="DP1"/>
</segment>
</net>
<net name="Сеть_9" class="0">
<segment>
<wire layer="91" width="0.1" x1="-38.1" y1="-287.02" x2="-35.56" y2="-287.02"/>
<pinref part="USBPULLUP" gate="PART_1" pin="2"/>
<pinref part="R10" gate="PART_1" pin="1"/>
</segment>
</net>
<net name="Сеть_10" class="0">
<segment>
<wire layer="91" width="0.1" x1="-10.16" y1="-299.72" x2="-24.13" y2="-299.72"/>
<wire layer="91" width="0.1" x1="-24.13" y1="-299.72" x2="-24.13" y2="-341.63"/>
<wire layer="91" width="0.1" x1="-24.13" y1="-341.63" x2="-82.55" y2="-341.63"/>
<pinref part="U7" gate="PART_1" pin="A9"/>
<pinref part="FPC" gate="PART_1" pin="15"/>
<wire layer="91" width="0.1" x1="-24.13" y1="-364.49" x2="-24.13" y2="-381"/>
<wire layer="91" width="0.1" x1="-24.13" y1="-341.63" x2="-24.13" y2="-364.49"/>
<wire layer="91" width="0.1" x1="-24.13" y1="-381" x2="-35.56" y2="-381"/>
<pinref part="ENCSW" gate="PART_1" pin="2"/>
<junction x="-24.13" y="-341.63"/>
<wire layer="91" width="0.1" x1="-27.94" y1="-364.49" x2="-24.13" y2="-364.49"/>
<wire layer="91" width="0.1" x1="-35.56" y1="-364.49" x2="-27.94" y2="-364.49"/>
<pinref part="ENCKP" gate="PART_1" pin="3"/>
<junction x="-24.13" y="-364.49"/>
<wire layer="91" width="0.1" x1="-33.02" y1="-316.23" x2="-27.94" y2="-316.23"/>
<wire layer="91" width="0.1" x1="-27.94" y1="-316.23" x2="-27.94" y2="-364.49"/>
<pinref part="R13" gate="PART_1" pin="2"/>
<junction x="-27.94" y="-364.49"/>
</segment>
</net>
<net name="Сеть_11" class="0">
<segment>
<wire layer="91" width="0.1" x1="-119.38" y1="-259.08" x2="-129.54" y2="-259.08"/>
<wire layer="91" width="0.1" x1="-129.54" y1="-259.08" x2="-129.54" y2="-251.46"/>
<wire layer="91" width="0.1" x1="-129.54" y1="-251.46" x2="-133.35" y2="-251.46"/>
<pinref part="IC1" gate="PART_1" pin="DM1"/>
<pinref part="J1" gate="PART_1" pin="D-"/>
</segment>
</net>
<net name="Сеть_13" class="0">
<segment>
<wire layer="91" width="0.1" x1="100.33" y1="-334.01" x2="85.09" y2="-334.01"/>
<wire layer="91" width="0.1" x1="85.09" y1="-334.01" x2="85.09" y2="-355.582"/>
<wire layer="91" width="0.1" x1="85.09" y1="-355.582" x2="35.564" y2="-355.582"/>
<pinref part="DB25" gate="PART_1" pin="P3"/>
<pinref part="U8" gate="PART_1" pin="B11"/>
<wire layer="91" width="0.1" x1="85.09" y1="-355.582" x2="85.09" y2="-365.76"/>
<wire layer="91" width="0.1" x1="85.09" y1="-365.76" x2="99.06" y2="-365.76"/>
<pinref part="STEPPERSHIELD" gate="PART_1" pin="4"/>
<junction x="85.09" y="-355.582"/>
</segment>
</net>
<net name="Сеть_15" class="0">
<segment>
<wire layer="91" width="0.1" x1="-91.44" y1="-248.92" x2="-72.39" y2="-248.92"/>
<pinref part="IC1" gate="PART_1" pin="DPU"/>
<pinref part="USB_IN" gate="PART_1" pin="D+"/>
</segment>
</net>
<net name="Сеть_16" class="0">
<segment>
<wire layer="91" width="0.1" x1="-137.16" y1="-382.27" x2="-134.303" y2="-382.27"/>
<wire layer="91" width="0.1" x1="-134.303" y1="-382.27" x2="-134.303" y2="-378.46"/>
<pinref part="DCIN" gate="PART_1" pin="1"/>
<pinref part="NetPort10" gate="PART_1" pin="+24V"/>
</segment>
<segment>
<wire layer="91" width="0.1" x1="16.51" y1="-215.9" x2="20.32" y2="-215.9"/>
<wire layer="91" width="0.1" x1="20.32" y1="-215.9" x2="20.32" y2="-243.84"/>
<wire layer="91" width="0.1" x1="20.32" y1="-243.84" x2="16.51" y2="-243.84"/>
<pinref part="U3" gate="PART_1" pin="VS"/>
<pinref part="U5" gate="PART_1" pin="VS"/>
<wire layer="91" width="0.1" x1="20.32" y1="-180.34" x2="20.32" y2="-184.15"/>
<wire layer="91" width="0.1" x1="20.32" y1="-184.15" x2="20.32" y2="-215.9"/>
<pinref part="NetPort1" gate="PART_1" pin="+24V"/>
<junction x="20.32" y="-215.9"/>
<wire layer="91" width="0.1" x1="20.32" y1="-184.15" x2="-11.43" y2="-184.15"/>
<wire layer="91" width="0.1" x1="-11.43" y1="-184.15" x2="-11.43" y2="-189.23"/>
<wire layer="91" width="0.1" x1="-11.43" y1="-189.23" x2="-7.62" y2="-189.23"/>
<pinref part="BLDC" gate="PART_1" pin="1"/>
<junction x="20.32" y="-184.15"/>
<wire layer="91" width="0.1" x1="20.32" y1="-184.15" x2="26.67" y2="-184.15"/>
<wire layer="91" width="0.1" x1="26.67" y1="-184.15" x2="26.67" y2="-186.69"/>
<pinref part="C1" gate="PART_1" pin="PLUS"/>
<junction x="20.32" y="-184.15"/>
</segment>
<segment>
<wire layer="91" width="0.1" x1="-82.55" y1="-372.11" x2="-77.47" y2="-372.11"/>
<wire layer="91" width="0.1" x1="-77.47" y1="-372.11" x2="-77.47" y2="-374.65"/>
<wire layer="91" width="0.1" x1="-77.47" y1="-374.65" x2="-82.55" y2="-374.65"/>
<pinref part="FPC" gate="PART_1" pin="3"/>
<pinref part="FPC" gate="PART_1" pin="2"/>
<wire layer="91" width="0.1" x1="-77.47" y1="-374.65" x2="-77.47" y2="-377.19"/>
<wire layer="91" width="0.1" x1="-77.47" y1="-377.19" x2="-82.55" y2="-377.19"/>
<pinref part="FPC" gate="PART_1" pin="1"/>
<junction x="-77.47" y="-374.65"/>
<wire layer="91" width="0.1" x1="-68.58" y1="-377.19" x2="-68.58" y2="-375.92"/>
<wire layer="91" width="0.1" x1="-77.47" y1="-377.19" x2="-68.58" y2="-377.19"/>
<pinref part="NetPort16" gate="PART_1" pin="+24V"/>
<junction x="-77.47" y="-377.19"/>
</segment>
<segment>
<wire layer="91" width="0.1" x1="106.68" y1="-347.98" x2="106.68" y2="-351.79"/>
<wire layer="91" width="0.1" x1="106.68" y1="-351.79" x2="96.52" y2="-351.79"/>
<wire layer="91" width="0.1" x1="96.52" y1="-351.79" x2="96.52" y2="-358.14"/>
<wire layer="91" width="0.1" x1="96.52" y1="-358.14" x2="99.06" y2="-358.14"/>
<pinref part="NetPort13" gate="PART_1" pin="+24V"/>
<pinref part="STEPPERSHIELD" gate="PART_1" pin="1"/>
</segment>
</net>
<net name="Сеть_18" class="0">
<segment>
<wire layer="91" width="0.1" x1="-8.89" y1="-254" x2="-21.59" y2="-254"/>
<pinref part="U5" gate="PART_1" pin="SR"/>
<pinref part="R9" gate="PART_1" pin="2"/>
</segment>
</net>
<net name="Сеть_19" class="0">
<segment>
<wire layer="91" width="0.1" x1="100.33" y1="-328.93" x2="83.82" y2="-328.93"/>
<wire layer="91" width="0.1" x1="83.82" y1="-328.93" x2="83.82" y2="-363.202"/>
<wire layer="91" width="0.1" x1="83.82" y1="-363.202" x2="35.564" y2="-363.202"/>
<pinref part="DB25" gate="PART_1" pin="P5"/>
<pinref part="U8" gate="PART_1" pin="B0"/>
<wire layer="91" width="0.1" x1="99.06" y1="-370.84" x2="83.82" y2="-370.84"/>
<wire layer="91" width="0.1" x1="83.82" y1="-370.84" x2="83.82" y2="-363.202"/>
<pinref part="STEPPERSHIELD" gate="PART_1" pin="6"/>
<junction x="83.82" y="-363.202"/>
</segment>
</net>
<net name="Сеть_20" class="0">
<segment>
<wire layer="91" width="0.1" x1="100.33" y1="-326.39" x2="82.55" y2="-326.39"/>
<wire layer="91" width="0.1" x1="82.55" y1="-326.39" x2="82.55" y2="-360.68"/>
<wire layer="91" width="0.1" x1="82.55" y1="-360.68" x2="35.564" y2="-360.68"/>
<pinref part="DB25" gate="PART_1" pin="P6"/>
<pinref part="U8" gate="PART_1" pin="B1"/>
<wire layer="91" width="0.1" x1="99.06" y1="-373.38" x2="82.55" y2="-373.38"/>
<wire layer="91" width="0.1" x1="82.55" y1="-373.38" x2="82.55" y2="-360.68"/>
<pinref part="STEPPERSHIELD" gate="PART_1" pin="7"/>
<junction x="82.55" y="-360.68"/>
</segment>
</net>
<net name="Сеть_21" class="0">
<segment>
<wire layer="91" width="0.1" x1="100.33" y1="-323.85" x2="81.28" y2="-323.85"/>
<wire layer="91" width="0.1" x1="81.28" y1="-323.85" x2="81.28" y2="-365.742"/>
<wire layer="91" width="0.1" x1="81.28" y1="-365.742" x2="35.564" y2="-365.742"/>
<pinref part="DB25" gate="PART_1" pin="P7"/>
<pinref part="U8" gate="PART_1" pin="A7"/>
<wire layer="91" width="0.1" x1="99.06" y1="-375.92" x2="81.28" y2="-375.92"/>
<wire layer="91" width="0.1" x1="81.28" y1="-375.92" x2="81.28" y2="-365.742"/>
<pinref part="STEPPERSHIELD" gate="PART_1" pin="8"/>
<junction x="81.28" y="-365.742"/>
</segment>
</net>
<net name="Сеть_22" class="0">
<segment>
<wire layer="91" width="0.1" x1="100.33" y1="-321.31" x2="80.01" y2="-321.31"/>
<wire layer="91" width="0.1" x1="80.01" y1="-378.46" x2="80.01" y2="-398.78"/>
<wire layer="91" width="0.1" x1="80.01" y1="-321.31" x2="80.01" y2="-378.46"/>
<wire layer="91" width="0.1" x1="80.01" y1="-398.78" x2="-16.51" y2="-398.78"/>
<wire layer="91" width="0.1" x1="-16.51" y1="-398.78" x2="-16.51" y2="-358.14"/>
<wire layer="91" width="0.1" x1="-16.51" y1="-358.14" x2="-10.16" y2="-358.14"/>
<pinref part="DB25" gate="PART_1" pin="P8"/>
<pinref part="U8" gate="PART_1" pin="A9"/>
<wire layer="91" width="0.1" x1="99.06" y1="-378.46" x2="80.01" y2="-378.46"/>
<pinref part="STEPPERSHIELD" gate="PART_1" pin="9"/>
<junction x="80.01" y="-378.46"/>
</segment>
</net>
<net name="Сеть_23" class="0">
<segment>
<wire layer="91" width="0.1" x1="-8.89" y1="-223.52" x2="-15.24" y2="-223.52"/>
<wire layer="91" width="0.1" x1="-15.24" y1="-237.49" x2="-15.24" y2="-251.46"/>
<wire layer="91" width="0.1" x1="-15.24" y1="-223.52" x2="-15.24" y2="-237.49"/>
<wire layer="91" width="0.1" x1="-15.24" y1="-251.46" x2="-8.89" y2="-251.46"/>
<pinref part="U3" gate="PART_1" pin="INH"/>
<pinref part="U5" gate="PART_1" pin="INH"/>
<wire layer="91" width="0.1" x1="-10.16" y1="-353.06" x2="-15.24" y2="-353.06"/>
<wire layer="91" width="0.1" x1="-15.24" y1="-353.06" x2="-15.24" y2="-251.46"/>
<pinref part="U8" gate="PART_1" pin="B15"/>
<junction x="-15.24" y="-251.46"/>
<wire layer="91" width="0.1" x1="-15.24" y1="-237.49" x2="-21.59" y2="-237.49"/>
<pinref part="R6" gate="PART_1" pin="2"/>
<junction x="-15.24" y="-237.49"/>
<wire layer="91" width="0.1" x1="-15.24" y1="-223.52" x2="-15.24" y2="-196.85"/>
<wire layer="91" width="0.1" x1="-15.24" y1="-196.85" x2="-7.62" y2="-196.85"/>
<pinref part="BLDC" gate="PART_1" pin="4"/>
<junction x="-15.24" y="-223.52"/>
</segment>
</net>
<net name="Сеть_24" class="0">
<segment>
<wire layer="91" width="0.1" x1="-91.44" y1="-246.38" x2="-81.28" y2="-246.38"/>
<wire layer="91" width="0.1" x1="-81.28" y1="-246.38" x2="-81.28" y2="-254"/>
<wire layer="91" width="0.1" x1="-81.28" y1="-254" x2="-72.39" y2="-254"/>
<pinref part="IC1" gate="PART_1" pin="DMU"/>
<pinref part="USB_IN" gate="PART_1" pin="D-"/>
</segment>
</net>
<net name="Сеть_25" class="0">
<segment>
<wire layer="91" width="0.1" x1="100.33" y1="-318.77" x2="78.74" y2="-318.77"/>
<wire layer="91" width="0.1" x1="78.74" y1="-381" x2="78.74" y2="-397.51"/>
<wire layer="91" width="0.1" x1="78.74" y1="-318.77" x2="78.74" y2="-381"/>
<wire layer="91" width="0.1" x1="78.74" y1="-397.51" x2="-15.24" y2="-397.51"/>
<wire layer="91" width="0.1" x1="-15.24" y1="-397.51" x2="-15.24" y2="-360.68"/>
<wire layer="91" width="0.1" x1="-15.24" y1="-360.68" x2="-10.16" y2="-360.68"/>
<pinref part="DB25" gate="PART_1" pin="P9"/>
<pinref part="U8" gate="PART_1" pin="A10"/>
<wire layer="91" width="0.1" x1="99.06" y1="-381" x2="78.74" y2="-381"/>
<pinref part="STEPPERSHIELD" gate="PART_1" pin="10"/>
<junction x="78.74" y="-381"/>
</segment>
</net>
<net name="Сеть_26" class="0">
<segment>
<wire layer="91" width="0.1" x1="100.33" y1="-298.45" x2="77.47" y2="-298.45"/>
<wire layer="91" width="0.1" x1="77.47" y1="-298.45" x2="77.47" y2="-368.282"/>
<wire layer="91" width="0.1" x1="77.47" y1="-368.282" x2="35.564" y2="-368.282"/>
<pinref part="DB25" gate="PART_1" pin="P17"/>
<pinref part="U8" gate="PART_1" pin="A6"/>
<wire layer="91" width="0.1" x1="99.06" y1="-383.54" x2="77.47" y2="-383.54"/>
<wire layer="91" width="0.1" x1="77.47" y1="-383.54" x2="77.47" y2="-368.282"/>
<pinref part="STEPPERSHIELD" gate="PART_1" pin="11"/>
<junction x="77.47" y="-368.282"/>
</segment>
</net>
<net name="Сеть_27" class="0">
<segment>
<wire layer="91" width="0.1" x1="-34.29" y1="-383.522" x2="-35.56" y2="-383.54"/>
<wire layer="91" width="0.1" x1="-34.29" y1="-383.522" x2="-10.16" y2="-383.522"/>
<pinref part="ENCSW" gate="PART_1" pin="1"/>
<pinref part="U8" gate="PART_1" pin="B8"/>
</segment>
</net>
<net name="Сеть_28" class="0">
<segment>
<wire layer="91" width="0.1" x1="-10.16" y1="-375.902" x2="-27.94" y2="-375.902"/>
<wire layer="91" width="0.1" x1="-27.94" y1="-375.902" x2="-27.94" y2="-378.46"/>
<wire layer="91" width="0.1" x1="-27.94" y1="-378.46" x2="-35.56" y2="-378.46"/>
<pinref part="U8" gate="PART_1" pin="B5"/>
<pinref part="ENCSW" gate="PART_1" pin="3"/>
</segment>
</net>
<net name="Сеть_29" class="0">
<segment>
<wire layer="91" width="0.1" x1="100.33" y1="-331.47" x2="87.63" y2="-331.47"/>
<wire layer="91" width="0.1" x1="87.63" y1="-331.47" x2="87.63" y2="-341.63"/>
<wire layer="91" width="0.1" x1="87.63" y1="-341.63" x2="-11.43" y2="-341.63"/>
<wire layer="91" width="0.1" x1="-11.43" y1="-341.63" x2="-11.43" y2="-345.44"/>
<wire layer="91" width="0.1" x1="-11.43" y1="-345.44" x2="-10.16" y2="-345.44"/>
<pinref part="DB25" gate="PART_1" pin="P4"/>
<pinref part="U8" gate="PART_1" pin="B12"/>
<wire layer="91" width="0.1" x1="87.63" y1="-341.63" x2="87.63" y2="-368.3"/>
<wire layer="91" width="0.1" x1="87.63" y1="-368.3" x2="99.06" y2="-368.3"/>
<pinref part="STEPPERSHIELD" gate="PART_1" pin="5"/>
<junction x="87.63" y="-341.63"/>
</segment>
</net>
<net name="Сеть_30" class="0">
<segment>
<wire layer="91" width="0.1" x1="104.14" y1="-240.03" x2="107.95" y2="-240.03"/>
<wire layer="91" width="0.1" x1="107.95" y1="-240.03" x2="107.95" y2="-242.57"/>
<wire layer="91" width="0.1" x1="107.95" y1="-242.57" x2="104.14" y2="-242.57"/>
<pinref part="U4" gate="PART_1" pin="N_OUT"/>
<pinref part="U4" gate="PART_1" pin="P_OUT"/>
<wire layer="91" width="0.1" x1="107.95" y1="-242.57" x2="128.27" y2="-242.57"/>
<pinref part="LAZERKP" gate="PART_1" pin="2"/>
<junction x="107.95" y="-242.57"/>
<wire layer="91" width="0.1" x1="107.95" y1="-242.57" x2="107.95" y2="-269.24"/>
<wire layer="91" width="0.1" x1="107.95" y1="-269.24" x2="92.71" y2="-269.24"/>
<wire layer="91" width="0.1" x1="92.71" y1="-269.24" x2="-72.39" y2="-269.24"/>
<wire layer="91" width="0.1" x1="-72.39" y1="-269.24" x2="-72.39" y2="-361.95"/>
<wire layer="91" width="0.1" x1="-72.39" y1="-361.95" x2="-82.55" y2="-361.95"/>
<pinref part="FPC" gate="PART_1" pin="7"/>
<junction x="107.95" y="-242.57"/>
<wire layer="91" width="0.1" x1="99.06" y1="-393.7" x2="92.71" y2="-393.7"/>
<wire layer="91" width="0.1" x1="92.71" y1="-393.7" x2="92.71" y2="-269.24"/>
<pinref part="STEPPERSHIELD" gate="PART_1" pin="15"/>
<junction x="92.71" y="-269.24"/>
</segment>
</net>
<net name="Сеть_31" class="0">
<segment>
<wire layer="91" width="0.1" x1="-8.89" y1="-226.06" x2="-21.59" y2="-226.06"/>
<pinref part="U3" gate="PART_1" pin="SR"/>
<pinref part="R5" gate="PART_1" pin="2"/>
</segment>
</net>
<net name="Сеть_34" class="0">
<segment>
<wire layer="91" width="0.1" x1="-10.16" y1="-350.52" x2="-17.78" y2="-350.52"/>
<wire layer="91" width="0.1" x1="-17.78" y1="-350.52" x2="-17.78" y2="-317.482"/>
<wire layer="91" width="0.1" x1="-17.78" y1="-317.482" x2="-17.78" y2="-220.98"/>
<wire layer="91" width="0.1" x1="-17.78" y1="-220.98" x2="-8.89" y2="-220.98"/>
<pinref part="U8" gate="PART_1" pin="B14"/>
<pinref part="U3" gate="PART_1" pin="IN"/>
<wire layer="91" width="0.1" x1="-17.78" y1="-220.98" x2="-21.59" y2="-220.98"/>
<pinref part="R3" gate="PART_1" pin="2"/>
<junction x="-17.78" y="-220.98"/>
<wire layer="91" width="0.1" x1="-17.78" y1="-220.98" x2="-17.78" y2="-191.77"/>
<wire layer="91" width="0.1" x1="-17.78" y1="-191.77" x2="-7.62" y2="-191.77"/>
<pinref part="BLDC" gate="PART_1" pin="2"/>
<junction x="-17.78" y="-220.98"/>
<wire layer="91" width="0.1" x1="-10.16" y1="-317.482" x2="-17.78" y2="-317.482"/>
<pinref part="U7" gate="PART_1" pin="B5"/>
<junction x="-17.78" y="-317.482"/>
</segment>
</net>
<net name="Сеть_35" class="0">
<segment>
<wire layer="91" width="0.1" x1="-10.16" y1="-347.962" x2="-16.51" y2="-347.962"/>
<wire layer="91" width="0.1" x1="-16.51" y1="-347.962" x2="-16.51" y2="-312.402"/>
<wire layer="91" width="0.1" x1="-16.51" y1="-312.402" x2="-16.51" y2="-248.92"/>
<wire layer="91" width="0.1" x1="-16.51" y1="-248.92" x2="-8.89" y2="-248.92"/>
<pinref part="U8" gate="PART_1" pin="B13"/>
<pinref part="U5" gate="PART_1" pin="IN"/>
<wire layer="91" width="0.1" x1="-16.51" y1="-248.92" x2="-21.59" y2="-248.92"/>
<pinref part="R8" gate="PART_1" pin="2"/>
<junction x="-16.51" y="-248.92"/>
<wire layer="91" width="0.1" x1="-16.51" y1="-248.92" x2="-16.51" y2="-194.31"/>
<wire layer="91" width="0.1" x1="-16.51" y1="-194.31" x2="-7.62" y2="-194.31"/>
<pinref part="BLDC" gate="PART_1" pin="3"/>
<junction x="-16.51" y="-248.92"/>
<wire layer="91" width="0.1" x1="-10.16" y1="-312.402" x2="-16.51" y2="-312.402"/>
<pinref part="U7" gate="PART_1" pin="B3"/>
<junction x="-16.51" y="-312.402"/>
</segment>
</net>
<net name="Сеть_36" class="0">
<segment>
<wire layer="91" width="0.1" x1="100.33" y1="-336.55" x2="86.36" y2="-336.55"/>
<wire layer="91" width="0.1" x1="86.36" y1="-336.55" x2="86.36" y2="-358.14"/>
<wire layer="91" width="0.1" x1="86.36" y1="-358.14" x2="35.564" y2="-358.14"/>
<pinref part="DB25" gate="PART_1" pin="P2"/>
<pinref part="U8" gate="PART_1" pin="B10"/>
<wire layer="91" width="0.1" x1="86.36" y1="-358.14" x2="86.36" y2="-363.22"/>
<wire layer="91" width="0.1" x1="86.36" y1="-363.22" x2="99.06" y2="-363.22"/>
<pinref part="STEPPERSHIELD" gate="PART_1" pin="3"/>
<junction x="86.36" y="-358.14"/>
</segment>
</net>
<net name="Сеть_37" class="0">
<segment>
<wire layer="91" width="0.1" x1="35.564" y1="-325.102" x2="41.91" y2="-325.102"/>
<wire layer="91" width="0.1" x1="41.91" y1="-325.102" x2="41.91" y2="-243.84"/>
<wire layer="91" width="0.1" x1="41.91" y1="-243.84" x2="66.04" y2="-243.84"/>
<wire layer="91" width="0.1" x1="66.04" y1="-243.84" x2="66.04" y2="-240.03"/>
<wire layer="91" width="0.1" x1="66.04" y1="-240.03" x2="73.66" y2="-240.03"/>
<pinref part="U7" gate="PART_1" pin="A0"/>
<pinref part="U4" gate="PART_1" pin="IN+"/>
<wire layer="91" width="0.1" x1="66.04" y1="-240.03" x2="60.96" y2="-240.03"/>
<pinref part="R7" gate="PART_1" pin="2"/>
<junction x="66.04" y="-240.03"/>
<wire layer="91" width="0.1" x1="41.91" y1="-325.102" x2="41.91" y2="-381"/>
<wire layer="91" width="0.1" x1="41.91" y1="-381" x2="46.99" y2="-381"/>
<pinref part="LAZERSW" gate="PART_1" pin="2"/>
<junction x="41.91" y="-325.102"/>
</segment>
</net>
<net name="Сеть_38" class="0">
<segment>
<wire layer="91" width="0.1" x1="35.564" y1="-380.982" x2="38.1" y2="-380.982"/>
<wire layer="91" width="0.1" x1="38.1" y1="-380.982" x2="38.1" y2="-209.55"/>
<wire layer="91" width="0.1" x1="38.1" y1="-209.55" x2="66.04" y2="-209.55"/>
<wire layer="91" width="0.1" x1="66.04" y1="-209.55" x2="66.04" y2="-205.74"/>
<wire layer="91" width="0.1" x1="66.04" y1="-205.74" x2="73.66" y2="-205.74"/>
<pinref part="U8" gate="PART_1" pin="A1"/>
<pinref part="U1" gate="PART_1" pin="IN+"/>
<wire layer="91" width="0.1" x1="66.04" y1="-205.74" x2="60.96" y2="-205.74"/>
<pinref part="R2" gate="PART_1" pin="2"/>
<junction x="66.04" y="-205.74"/>
</segment>
</net>
<net name="Сеть_39" class="0">
<segment>
<wire layer="91" width="0.1" x1="-10.16" y1="-304.8" x2="-12.7" y2="-304.8"/>
<wire layer="91" width="0.1" x1="-12.7" y1="-304.8" x2="-12.7" y2="-363.202"/>
<wire layer="91" width="0.1" x1="-12.7" y1="-363.202" x2="-10.16" y2="-363.202"/>
<pinref part="U7" gate="PART_1" pin="A11"/>
<pinref part="U8" gate="PART_1" pin="A11"/>
<wire layer="91" width="0.1" x1="-119.38" y1="-236.22" x2="-121.92" y2="-236.22"/>
<wire layer="91" width="0.1" x1="-121.92" y1="-236.22" x2="-121.92" y2="-304.8"/>
<wire layer="91" width="0.1" x1="-121.92" y1="-304.8" x2="-12.7" y2="-304.8"/>
<pinref part="IC1" gate="PART_1" pin="DM4"/>
<junction x="-12.7" y="-304.8"/>
</segment>
</net>
<net name="Сеть_40" class="0">
<segment>
<wire layer="91" width="0.1" x1="-10.16" y1="-307.34" x2="-13.97" y2="-307.34"/>
<wire layer="91" width="0.1" x1="-13.97" y1="-307.34" x2="-13.97" y2="-365.76"/>
<wire layer="91" width="0.1" x1="-13.97" y1="-365.76" x2="-10.16" y2="-365.76"/>
<pinref part="U7" gate="PART_1" pin="A12"/>
<pinref part="U8" gate="PART_1" pin="A12"/>
<wire layer="91" width="0.1" x1="-13.97" y1="-307.34" x2="-36.83" y2="-307.34"/>
<wire layer="91" width="0.1" x1="-36.83" y1="-289.56" x2="-38.1" y2="-289.56"/>
<wire layer="91" width="0.1" x1="-36.83" y1="-307.34" x2="-36.83" y2="-289.56"/>
<pinref part="USBPULLUP" gate="PART_1" pin="1"/>
<junction x="-13.97" y="-307.34"/>
<wire layer="91" width="0.1" x1="-119.38" y1="-233.68" x2="-123.19" y2="-233.68"/>
<wire layer="91" width="0.1" x1="-123.19" y1="-233.68" x2="-123.19" y2="-307.34"/>
<wire layer="91" width="0.1" x1="-123.19" y1="-307.34" x2="-36.83" y2="-307.34"/>
<pinref part="IC1" gate="PART_1" pin="DP4"/>
<junction x="-36.83" y="-307.34"/>
</segment>
</net>
<net name="Сеть_41" class="0">
<segment>
<wire layer="91" width="0.1" x1="-119.38" y1="-203.2" x2="-121.92" y2="-203.2"/>
<wire layer="91" width="0.1" x1="-121.92" y1="-203.2" x2="-121.92" y2="-205.74"/>
<wire layer="91" width="0.1" x1="-121.92" y1="-205.74" x2="-119.38" y2="-205.74"/>
<pinref part="IC1" gate="PART_1" pin="XRSTJ"/>
<pinref part="IC1" gate="PART_1" pin="VBUSM"/>
<wire layer="91" width="0.1" x1="-121.92" y1="-205.74" x2="-121.92" y2="-208.28"/>
<wire layer="91" width="0.1" x1="-121.92" y1="-208.28" x2="-119.38" y2="-208.28"/>
<pinref part="IC1" gate="PART_1" pin="BUSJ"/>
<junction x="-121.92" y="-205.74"/>
<wire layer="91" width="0.1" x1="-119.38" y1="-226.06" x2="-121.92" y2="-226.06"/>
<wire layer="91" width="0.1" x1="-121.92" y1="-226.06" x2="-121.92" y2="-208.28"/>
<pinref part="IC1" gate="PART_1" pin="OVCJ"/>
<junction x="-121.92" y="-208.28"/>
<wire layer="91" width="0.1" x1="-91.44" y1="-223.52" x2="-88.9" y2="-223.52"/>
<wire layer="91" width="0.1" x1="-88.9" y1="-223.52" x2="-73.66" y2="-223.52"/>
<wire layer="91" width="0.1" x1="-73.66" y1="-223.52" x2="-73.66" y2="-189.23"/>
<wire layer="91" width="0.1" x1="-73.66" y1="-189.23" x2="-121.92" y2="-189.23"/>
<wire layer="91" width="0.1" x1="-121.92" y1="-189.23" x2="-121.92" y2="-203.2"/>
<pinref part="IC1" gate="PART_1" pin="VD33_O"/>
<junction x="-121.92" y="-203.2"/>
<wire layer="91" width="0.1" x1="-91.44" y1="-220.98" x2="-88.9" y2="-220.98"/>
<wire layer="91" width="0.1" x1="-88.9" y1="-220.98" x2="-88.9" y2="-223.52"/>
<pinref part="IC1" gate="PART_1" pin="VD33"/>
<junction x="-88.9" y="-223.52"/>
<wire layer="91" width="0.1" x1="-73.66" y1="-223.52" x2="-67.31" y2="-223.52"/>
<junction x="-73.66" y="-223.52"/>
<junction x="-67.31" y="-223.52"/>
<wire layer="91" width="0.1" x1="-67.31" y1="-218.44" x2="-66.04" y2="-218.44"/>
<wire layer="91" width="0.1" x1="-67.31" y1="-223.52" x2="-66.04" y2="-223.52"/>
<wire layer="91" width="0.1" x1="-67.31" y1="-218.44" x2="-67.31" y2="-223.52"/>
<pinref part="C4" gate="PART_1" pin="PLUS"/>
<pinref part="C5" gate="PART_1" pin="1"/>
</segment>
</net>
<net name="Сеть_42" class="0">
<segment>
<wire layer="91" width="0.1" x1="-91.44" y1="-213.36" x2="-88.9" y2="-213.36"/>
<wire layer="91" width="0.1" x1="-88.9" y1="-213.36" x2="-88.9" y2="-215.9"/>
<wire layer="91" width="0.1" x1="-88.9" y1="-215.9" x2="-91.44" y2="-215.9"/>
<pinref part="IC1" gate="PART_1" pin="VD18"/>
<pinref part="IC1" gate="PART_1" pin="VD18_O"/>
<wire layer="91" width="0.1" x1="-88.9" y1="-213.36" x2="-67.31" y2="-213.36"/>
<junction x="-88.9" y="-213.36"/>
<junction x="-67.31" y="-213.36"/>
<wire layer="91" width="0.1" x1="-67.31" y1="-208.28" x2="-66.04" y2="-208.28"/>
<wire layer="91" width="0.1" x1="-67.31" y1="-213.36" x2="-66.04" y2="-213.36"/>
<wire layer="91" width="0.1" x1="-67.31" y1="-208.28" x2="-67.31" y2="-213.36"/>
<pinref part="C2" gate="PART_1" pin="1"/>
<pinref part="C3" gate="PART_1" pin="PLUS"/>
</segment>
</net>
<net name="Сеть_43" class="0">
<segment>
<wire layer="91" width="0.1" x1="-125.73" y1="-198.12" x2="-119.38" y2="-198.12"/>
<pinref part="R1" gate="PART_1" pin="2"/>
<pinref part="IC1" gate="PART_1" pin="REXT"/>
</segment>
</net>
<net name="Сеть_44" class="0">
<segment>
<wire layer="91" width="0.1" x1="35.564" y1="-383.54" x2="35.564" y2="-383.522"/>
<wire layer="91" width="0.1" x1="35.564" y1="-383.54" x2="46.99" y2="-383.54"/>
<pinref part="U8" gate="PART_1" pin="A0"/>
<pinref part="LAZERSW" gate="PART_1" pin="3"/>
</segment>
</net>
<net name="Сеть_45" class="0">
<segment>
<wire layer="91" width="0.1" x1="35.564" y1="-378.46" x2="35.564" y2="-378.442"/>
<wire layer="91" width="0.1" x1="35.564" y1="-378.46" x2="46.99" y2="-378.46"/>
<pinref part="U8" gate="PART_1" pin="A2"/>
<pinref part="LAZERSW" gate="PART_1" pin="1"/>
</segment>
</net>
<net name="Сеть_46" class="0">
<segment>
<wire layer="91" width="0.1" x1="128.27" y1="-205.74" x2="104.14" y2="-205.74"/>
<pinref part="XP2" gate="PART_1" pin="1"/>
<pinref part="U1" gate="PART_1" pin="N_OUT"/>
</segment>
</net>
<net name="Сеть_47" class="0">
<segment>
<wire layer="91" width="0.1" x1="104.14" y1="-208.28" x2="128.27" y2="-208.28"/>
<pinref part="U1" gate="PART_1" pin="P_OUT"/>
<pinref part="XP2" gate="PART_1" pin="2"/>
</segment>
</net>
<net name="Сеть_48" class="0">
<segment>
<wire layer="91" width="0.1" x1="127" y1="-215.9" x2="128.27" y2="-215.9"/>
<wire layer="91" width="0.1" x1="127" y1="-218.44" x2="128.27" y2="-218.44"/>
<wire layer="91" width="0.1" x1="127" y1="-215.9" x2="127" y2="-218.44"/>
<pinref part="XP3" gate="PART_1" pin="1"/>
<pinref part="XP3" gate="PART_1" pin="2"/>
<wire layer="91" width="0.1" x1="127" y1="-218.44" x2="127" y2="-219.71"/>
<pinref part="R4" gate="PART_1" pin="1"/>
<junction x="127" y="-218.44"/>
</segment>
</net>
<net name="Сеть_49" class="0">
<segment>
<wire layer="91" width="0.1" x1="127" y1="-240.03" x2="128.27" y2="-240.03"/>
<wire layer="91" width="0.1" x1="127" y1="-232.41" x2="127" y2="-240.03"/>
<pinref part="R4" gate="PART_1" pin="2"/>
<pinref part="LAZERKP" gate="PART_1" pin="1"/>
<wire layer="91" width="0.1" x1="-82.55" y1="-339.09" x2="-73.66" y2="-339.09"/>
<wire layer="91" width="0.1" x1="-73.66" y1="-339.09" x2="-73.66" y2="-267.97"/>
<wire layer="91" width="0.1" x1="93.98" y1="-267.97" x2="127" y2="-267.97"/>
<wire layer="91" width="0.1" x1="-73.66" y1="-267.97" x2="93.98" y2="-267.97"/>
<wire layer="91" width="0.1" x1="127" y1="-267.97" x2="127" y2="-240.03"/>
<pinref part="FPC" gate="PART_1" pin="16"/>
<junction x="127" y="-240.03"/>
<wire layer="91" width="0.1" x1="99.06" y1="-391.16" x2="93.98" y2="-391.16"/>
<wire layer="91" width="0.1" x1="93.98" y1="-391.16" x2="93.98" y2="-267.97"/>
<pinref part="STEPPERSHIELD" gate="PART_1" pin="14"/>
<junction x="93.98" y="-267.97"/>
</segment>
</net>
<net name="Сеть_12" class="0">
<segment>
<wire layer="91" width="0.1" x1="-119.38" y1="-241.3" x2="-124.46" y2="-241.3"/>
<wire layer="91" width="0.1" x1="-124.46" y1="-241.3" x2="-124.46" y2="-309.88"/>
<wire layer="91" width="0.1" x1="-124.46" y1="-309.88" x2="-74.93" y2="-309.88"/>
<wire layer="91" width="0.1" x1="-74.93" y1="-309.88" x2="-74.93" y2="-328.93"/>
<wire layer="91" width="0.1" x1="-74.93" y1="-328.93" x2="-82.55" y2="-328.93"/>
<pinref part="IC1" gate="PART_1" pin="DP3"/>
<pinref part="FPC" gate="PART_1" pin="20"/>
</segment>
</net>
<net name="Сеть_14" class="0">
<segment>
<wire layer="91" width="0.1" x1="-82.55" y1="-326.39" x2="-76.2" y2="-326.39"/>
<wire layer="91" width="0.1" x1="-76.2" y1="-326.39" x2="-76.2" y2="-311.15"/>
<wire layer="91" width="0.1" x1="-76.2" y1="-311.15" x2="-125.73" y2="-311.15"/>
<wire layer="91" width="0.1" x1="-125.73" y1="-311.15" x2="-125.73" y2="-243.84"/>
<wire layer="91" width="0.1" x1="-125.73" y1="-243.84" x2="-119.38" y2="-243.84"/>
<pinref part="FPC" gate="PART_1" pin="21"/>
<pinref part="IC1" gate="PART_1" pin="DM3"/>
</segment>
</net>
<net name="Сеть_17" class="0">
<segment>
<wire layer="91" width="0.1" x1="72.39" y1="-308.61" x2="69.85" y2="-308.61"/>
<wire layer="91" width="0.1" x1="100.33" y1="-308.61" x2="72.39" y2="-308.61"/>
<pinref part="DB25" gate="PART_1" pin="P13"/>
<pinref part="R12" gate="PART_1" pin="2"/>
<wire layer="91" width="0.1" x1="72.39" y1="-386.08" x2="72.39" y2="-400.05"/>
<wire layer="91" width="0.1" x1="72.39" y1="-308.61" x2="72.39" y2="-386.08"/>
<wire layer="91" width="0.1" x1="72.39" y1="-400.05" x2="-13.97" y2="-400.05"/>
<wire layer="91" width="0.1" x1="-13.97" y1="-400.05" x2="-13.97" y2="-386.08"/>
<wire layer="91" width="0.1" x1="-13.97" y1="-386.08" x2="-10.16" y2="-386.08"/>
<pinref part="U8" gate="PART_1" pin="B9"/>
<junction x="72.39" y="-308.61"/>
<wire layer="91" width="0.1" x1="99.06" y1="-386.08" x2="72.39" y2="-386.08"/>
<pinref part="STEPPERSHIELD" gate="PART_1" pin="12"/>
<junction x="72.39" y="-386.08"/>
</segment>
</net>
<net name="Сеть_32" class="0">
<segment>
<wire layer="91" width="0.1" x1="69.85" y1="-303.53" x2="73.66" y2="-303.53"/>
<wire layer="91" width="0.1" x1="73.66" y1="-303.53" x2="100.33" y2="-303.53"/>
<pinref part="R11" gate="PART_1" pin="2"/>
<pinref part="DB25" gate="PART_1" pin="P15"/>
<wire layer="91" width="0.1" x1="-10.16" y1="-381" x2="-12.7" y2="-381"/>
<wire layer="91" width="0.1" x1="-12.7" y1="-381" x2="-12.7" y2="-396.24"/>
<wire layer="91" width="0.1" x1="-12.7" y1="-396.24" x2="73.66" y2="-396.24"/>
<wire layer="91" width="0.1" x1="73.66" y1="-396.24" x2="73.66" y2="-388.62"/>
<wire layer="91" width="0.1" x1="73.66" y1="-388.62" x2="73.66" y2="-303.53"/>
<pinref part="U8" gate="PART_1" pin="B7"/>
<junction x="73.66" y="-303.53"/>
<wire layer="91" width="0.1" x1="99.06" y1="-388.62" x2="73.66" y2="-388.62"/>
<pinref part="STEPPERSHIELD" gate="PART_1" pin="13"/>
<junction x="73.66" y="-388.62"/>
</segment>
</net>
</nets>
</sheet>
</sheets>
</schematic>
</drawing>
</eagle>

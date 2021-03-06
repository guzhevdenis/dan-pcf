importClass(Packages.org.csstudio.opibuilder.scriptUtil.DataUtil);
importClass(Packages.org.csstudio.opibuilder.scriptUtil.PVUtil);
importClass(Packages.org.csstudio.opibuilder.scriptUtil.ScriptUtil);
importClass(Packages.org.csstudio.opibuilder.scriptUtil.ConsoleUtil);

var table = widget.getTable();
var fct_name=widget.getPropertyValue("name");
var selectionChanged  = new Packages.org.csstudio.swt.widgets.natives.SpreadSheetTable.ITableSelectionChangedListener() {
    selectionChanged: function(selection) {
    	
    	var selectedrow=  table.getSelection();
    	var cuName=selectedrow[0][0];
		var phyName=selectedrow[0][1];
		
        // change $(CU) substitution
        var macroInput = DataUtil.createMacrosInput(true);
        macroInput.put("CU", cuName);
        macroInput.put("PHY_NAME", phyName)
        macroInput.put("FCT_NAME", fct_name);
        macroInput.put("SHOW_PLC_IOC", "false");
        // open OPI
        // see https://svnpub.iter.org/codac/iter/codac/dev/units/m-css-boy/trunk/org.csstudio.opibuilder/src/org/csstudio/opibuilder/scriptUtil/ScriptUtil.java
        ScriptUtil.openOPI(widget, fct_name+"-"+cuName+"-SRVDetails.opi", 1, macroInput);
	}
};
table.addSelectionChangedListener(selectionChanged); 

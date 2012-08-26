

		
       	You can use the accompanying source code of the application as you like.

	The TAPI3.h file accompanying is a slight modification of the 
	original TAPI3.h file (VC++),which I had to modify to make it compatible
	with the latest tapi32.dll servers available more commonly.
		
	You'd have to replace the original file with this one 
	if you want to work on the source code of TelePathy software.
	It is anyhow completely backwards compatible and runs as cleanly
       	as the original in all respects.

	Still i'd want you to backup your original TAPI3.h file 
	before you replace it with my one.
		
	Next,if you get an error message regarding linking to t3iid.lib or ole32.lib
	when you try to build the application ,just remove the reference
	to t3iid.lib & ole32.lib from the file-view and re-add the same refrences browsing
	from Project->Add to project->files into the 'Lib' folder of your 'VC' folder in 
	Microsoft Visual Studio Installation Folder.
		
	Also You must use the GUIControl.ocx which provides TelePathy its Cool!looks 		
	to run TelePathy properly.However you can do without it.You can provide your
	own interface .Just remove the control from above the dialog IDD_TELEPATHY
	which is hidden behind the control .But do not remove the MCI control and the 				
	ListBox Control (m_List) which are also in hidden state somewhere on the same 
	dialog,behind the control's UI.


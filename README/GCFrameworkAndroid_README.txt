Gamer camp notes

1) building
^^^^^^^^^^^

need to install the VS tools for android development:
Tools -> Get Tools and Features (see VS2017AdditionalInstallOptions.png for the details of what to select)

	* open proj.visualstudio/GCTemplateAndroid.androidproj
	
	* build the build_android project
	
	* select "GCTemplate" as the startup project
	
	* click "show all files" button at the top of the solution explorer window
	
	* refresh the assets folder by doign the following:
		* right click on the "assets" folder under GCTemplate & choose "exclude from project"
		* right click on the "assets" folder under GCTemplate again & choose "Include in project"
		* it's possible to partially (maybe completely?) automate this (see below) 
	

	troubleshooting
	^^^^^^^^^^^^^^^
	if coompilation faisl saying it can't find clang open regedit & check

		Computer\HKEY_CURRENT_USER\Software\Microsoft\VisualStudio\SecondaryInstaller\VC 

	& make sure the values there are correct (the VS installer set them incorrectly for me, in fact I just deleted the whole registry key which causes it to check the files off your actual HDD)

	

2) you can grab the Visual Studio android emulator to debug
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
https://visualstudio.microsoft.com/vs/msft-android-emulator/

	note: 
	running the VS Android emulator needs the "x86" version of the android project to be built 

	troubleshooting
	^^^^^^^^^^^^^^^
	problem deploying apk to emulator / connecting debugger to emulator
	https://nicksnettravels.builttoroam.com/post/2017/01/29/Unable-to-Connect-or-Debug-to-Visual-Studio-Android-Emulator-with-Visual-Studio-2017-RC.aspx


	
3) the android emulator should work fine too 
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
(installed with the VS android stuff)

	troubleshooting
	^^^^^^^^^^^^^^^
	https://docs.microsoft.com/en-us/xamarin/android/get-started/installation/android-emulator/troubleshooting?pivots=windows

	
	
4) you can also deploy to device
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
* you need to trun on developer mode	
* enable USB debugging
* install the android USB drivers (if your PC doesn't auto-detect and install them for you)

	troubleshooting
	^^^^^^^^^^^^^^^
	won't detect your android device
	https://stackoverflow.com/questions/38224370/visual-studio-and-android-device-monitor-doesnt-detect-any-devices#51594570
	
	
5)automate the refesh assets folder step
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Download this Visual Studio extension https://marketplace.visualstudio.com/items?itemName=SergeyVlasov.VisualCommander

Create a new command ( you may need to look at the docs...) & paste the following into it:

public class C : VisualCommanderExt.ICommand
{
	public void Run( EnvDTE80.DTE2 DTE, Microsoft.VisualStudio.Shell.Package package )
	{
		string solutionName = "";

		try
		{
			solutionName = DTE.Solution.Properties.Item( "Name" ).Value.ToString();
		}
		catch( System.Exception ex )
		{
			System.Windows.Forms.MessageBox.Show( ex.ToString() );
		}

		string projectName = "";
		EnvDTE.UIHierarchyItem cUIHItem = null;

		foreach( EnvDTE.Project cProject in DTE.Solution.Projects )
		{
			//System.Windows.Forms.MessageBox.Show( cProject.Kind.ToString() );

			EnvDTE.UIHierarchy solutionExplorer = DTE.ToolWindows.SolutionExplorer;

			string strAssetFolderPath = "";

			try
			{
				string strProjName 	= cProject.Name;
				strAssetFolderPath	= solutionName + "\\" + strProjName + "\\assets";
				cUIHItem 		= solutionExplorer.GetItem( strAssetFolderPath );
			}
			catch (System.Exception ex)
			{
				System.Windows.Forms.MessageBox.Show( ex.ToString() );
			}	

			if( null != cUIHItem )
			{
				System.Windows.Forms.MessageBox.Show( "found " + strAssetFolderPath );
				break;
			}
		}

		if( null != cUIHItem )
		{
			EnvDTE.UIHierarchy solutionExplorer = DTE.ToolWindows.SolutionExplorer;

			try
			{
				cUIHItem.Select(EnvDTE.vsUISelectionType.vsUISelectionTypeSelect);
			}
			catch (System.Exception ex)
			{
				System.Windows.Forms.MessageBox.Show( "failed to select item " + ex.ToString() );
			}	

			try
			{
				DTE.ExecuteCommand( "Project.ExcludeFromProject" );
			}
			catch( System.Exception ex )
			{
				System.Windows.Forms.MessageBox.Show( cUIHItem.Name + " couldn't be excluded." );
			}
			DTE.ExecuteCommand( "Project.IncludeInProject" );
		}
		else
		{
			System.Windows.Forms.MessageBox.Show( "didn't find assets folder" );
		}	
	}
}

package xmlvalidator;

import java.io.*;
import java.util.*;

import org.eclipse.swt.*;
import org.eclipse.swt.events.*;
import org.eclipse.swt.graphics.*;
import org.eclipse.swt.layout.*;
import org.eclipse.swt.widgets.*;
import org.eclipse.wb.swt.*;

public class MainWindow {

	protected Shell shell;
	Properties appSettings = new Properties();
	Cursor defaultCursor; // To change the cursor to an arrow at any point after MainWindow() has executed, use
							// shell.setCursor(defaultCursor);
	Cursor waitCursor; // To change the cursor to an hourglass at any point after MainWindow() has executed, use
						// shell.setCursor(waitCursor);
	private Composite clientArea;
	private Label statusText;


	/**
	 * Launch the application.
	 * 
	 * @param args
	 */
	public static void main(String[] args) {
		try {
			MainWindow window = new MainWindow();
			window.open();
		} catch (Exception e) {
			e.printStackTrace();
		}
	}


	/**
	 * Open the window.
	 */
	public void open() {
		Display display = Display.getDefault();
		createContents();

		setPreferences();
		waitCursor = shell.getDisplay().getSystemCursor(SWT.CURSOR_WAIT);
		defaultCursor = shell.getDisplay().getSystemCursor(SWT.CURSOR_ARROW);
		clientArea.setFocus();

		shell.open();
		shell.layout();
		while (!shell.isDisposed()) {
			if (!display.readAndDispatch()) {
				display.sleep();
			}
		}
	}


	// Load application settings from .ini file
	private void setPreferences() {
		try {
			appSettings.load(new FileInputStream("appsettings.ini"));
		} catch (FileNotFoundException e) {
		} catch (IOException e) {
		}

		// By default, center window
		int width = Integer.parseInt(appSettings.getProperty("width", "640"));
		int height = Integer.parseInt(appSettings.getProperty("height", "480"));
		Rectangle screenBounds = shell.getDisplay().getBounds();
		int defaultTop = (screenBounds.height - height) / 2;
		int defaultLeft = (screenBounds.width - width) / 2;
		int top = Integer.parseInt(appSettings.getProperty("top", String.valueOf(defaultTop)));
		int left = Integer.parseInt(appSettings.getProperty("left", String.valueOf(defaultLeft)));
		shell.setSize(width, height);
		shell.setLocation(left, top);
		saveShellBounds();
	}


	// Save window location in appSettings hash table
	private void saveShellBounds() {
		// Save window bounds in app settings
		Rectangle bounds = shell.getBounds();
		appSettings.setProperty("top", String.valueOf(bounds.y));
		appSettings.setProperty("left", String.valueOf(bounds.x));
		appSettings.setProperty("width", String.valueOf(bounds.width));
		appSettings.setProperty("height", String.valueOf(bounds.height));
	}


	/**
	 * Create contents of the window.
	 */
	protected void createContents() {
		shell = new Shell();
		shell.addControlListener(new ShellControlListener());
		shell.addDisposeListener(new ShellDisposeListener());
		shell.setImage(SWTResourceManager.getImage(MainWindow.class, "/images/16x16.png"));
		shell.setSize(640, 480);
		shell.setText("Change This Title");
		GridLayout gl_shell = new GridLayout(1, false);
		gl_shell.marginHeight = 3;
		gl_shell.marginWidth = 3;
		shell.setLayout(gl_shell);

		Menu menu = new Menu(shell, SWT.BAR);
		shell.setMenuBar(menu);

		MenuItem fileMenuItem = new MenuItem(menu, SWT.CASCADE);
		fileMenuItem.setText("&File");

		Menu menu_1 = new Menu(fileMenuItem);
		fileMenuItem.setMenu(menu_1);

		MenuItem newFileMenuItem = new MenuItem(menu_1, SWT.NONE);
		newFileMenuItem.setImage(SWTResourceManager.getImage(MainWindow.class, "/images/new.gif"));
		newFileMenuItem.setText("&New");

		MenuItem openFileMenuItem = new MenuItem(menu_1, SWT.NONE);
		openFileMenuItem.addSelectionListener(new OpenFileMenuItemSelectionListener());
		openFileMenuItem.setImage(SWTResourceManager.getImage(MainWindow.class, "/images/open.gif"));
		openFileMenuItem.setText("&Open");

		MenuItem closeFileMenuItem = new MenuItem(menu_1, SWT.NONE);
		closeFileMenuItem.setText("&Close");

		new MenuItem(menu_1, SWT.SEPARATOR);

		MenuItem saveFileMenuItem = new MenuItem(menu_1, SWT.NONE);
		saveFileMenuItem.setImage(SWTResourceManager.getImage(MainWindow.class, "/images/save.gif"));
		saveFileMenuItem.setText("&Save");

		new MenuItem(menu_1, SWT.SEPARATOR);

		MenuItem exitMenuItem = new MenuItem(menu_1, SWT.NONE);
		exitMenuItem.addSelectionListener(new ExitMenuItemSelectionListener());
		exitMenuItem.setText("E&xit");

		MenuItem helpMenuItem = new MenuItem(menu, SWT.CASCADE);
		helpMenuItem.setText("&Help");

		Menu menu_2 = new Menu(helpMenuItem);
		helpMenuItem.setMenu(menu_2);

		MenuItem aboutMenuItem = new MenuItem(menu_2, SWT.NONE);
		aboutMenuItem.addSelectionListener(new AboutMenuItemSelectionListener());
		aboutMenuItem.setText("&About");

		ToolBar toolBar = new ToolBar(shell, SWT.FLAT | SWT.RIGHT);
		toolBar.setLayoutData(new GridData(SWT.FILL, SWT.CENTER, false, false, 1, 1));

		ToolItem newToolItem = new ToolItem(toolBar, SWT.NONE);
		newToolItem.setToolTipText("New");
		newToolItem.setImage(SWTResourceManager.getImage(MainWindow.class, "/images/new.gif"));

		ToolItem openToolItem = new ToolItem(toolBar, SWT.NONE);
		openToolItem.addSelectionListener(new OpenToolItemSelectionListener());
		openToolItem.setToolTipText("Open");
		openToolItem.setImage(SWTResourceManager.getImage(MainWindow.class, "/images/open.gif"));

		ToolItem saveToolItem = new ToolItem(toolBar, SWT.NONE);
		saveToolItem.setToolTipText("Save");
		saveToolItem.setImage(SWTResourceManager.getImage(MainWindow.class, "/images/save.gif"));

		Label label = new Label(shell, SWT.SEPARATOR | SWT.HORIZONTAL | SWT.SHADOW_IN);
		label.setLayoutData(new GridData(SWT.FILL, SWT.CENTER, false, false, 1, 1));

		clientArea = new Composite(shell, SWT.NONE);
		clientArea.setLayoutData(new GridData(SWT.FILL, SWT.FILL, true, true, 1, 1));

		Label label_1 = new Label(shell, SWT.SEPARATOR | SWT.HORIZONTAL | SWT.SHADOW_IN);
		label_1.setLayoutData(new GridData(SWT.FILL, SWT.CENTER, false, false, 1, 1));

		Composite statusArea = new Composite(shell, SWT.NONE);
		statusArea.setBackground(SWTResourceManager.getColor(SWT.COLOR_WIDGET_BACKGROUND));
		FillLayout fl_statusArea = new FillLayout(SWT.HORIZONTAL);
		fl_statusArea.marginWidth = 2;
		fl_statusArea.marginHeight = 2;
		statusArea.setLayout(fl_statusArea);
		GridData gd_statusArea = new GridData(SWT.FILL, SWT.CENTER, true, false, 1, 1);
		gd_statusArea.widthHint = 125;
		statusArea.setLayoutData(gd_statusArea);

		statusText = new Label(statusArea, SWT.NONE);
		statusText.setText("Ready");

	}


	private void handleFileOpenRequest() {
		FileDialog dialog = new FileDialog(shell, SWT.OPEN);
		String filename = dialog.open();
		if (filename != null) {
			shell.setText(filename);
		}
	}


	private class ExitMenuItemSelectionListener extends SelectionAdapter {

		@Override
		public void widgetSelected(SelectionEvent e) {
			try {
				// Save app settings to file
				appSettings.store(new FileOutputStream("appsettings.ini"), "");
			} catch (Exception ex) {
			}
			shell.dispose();
		}
	}


	private class OpenFileMenuItemSelectionListener extends SelectionAdapter {

		@Override
		public void widgetSelected(SelectionEvent e) {
			handleFileOpenRequest();
		}
	}


	private class OpenToolItemSelectionListener extends SelectionAdapter {

		@Override
		public void widgetSelected(SelectionEvent e) {
			handleFileOpenRequest();
		}
	}


	private class AboutMenuItemSelectionListener extends SelectionAdapter {

		@Override
		public void widgetSelected(SelectionEvent e) {
			MessageBox message = new MessageBox(shell, SWT.OK | SWT.ICON_INFORMATION);
			message.setText("About Change_This_Title");
			message.setMessage("Change this about message\n\nApplicationName v1.0");
			message.open();
		}
	}


	private class ShellDisposeListener implements DisposeListener {

		public void widgetDisposed(DisposeEvent arg0) {
			try {
				// Save app settings to file
				appSettings.store(new FileOutputStream("appsettings.ini"), "");
			} catch (Exception ex) {
			}
		}
	}


	private class ShellControlListener extends ControlAdapter {

		@Override
		public void controlMoved(ControlEvent e) {
			try {
				saveShellBounds();
			} catch (Exception ex) {
				setStatus(ex.getMessage());
			}
		}


		@Override
		public void controlResized(ControlEvent e) {
			try {
				saveShellBounds();
			} catch (Exception ex) {
				setStatus(ex.getMessage());
			}
		}
	}


	private void setStatus(String message) {
		statusText.setText(message);
	}

}

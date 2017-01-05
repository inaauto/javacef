package org.embedded.browser;

import java.util.HashMap;
import java.util.Iterator;
import java.util.Map.Entry;

public class ChromeSettings {
	
	/**
	 * The log severity. Only messages of this severity level or higher will be
	 * logged. Values are:
	 *   0 = LOGSEVERITY_DEFAULT - Default logging (currently INFO logging)
	 *   1 = LOGSEVERITY_VERBOSE
	 *   2 = LOGSEVERITY_INFO
	 *   3 = LOGSEVERITY_WARNING
	 *   4 = LOGSEVERITY_ERROR
	 *  99 = LOGSEVERITY_DISABLE - Completely disable logging
	 */
	public enum LogSeverity {
		LOGSEVERITY_DEFAULT(0),
		LOGSEVERITY_VERBOSE(1),
		LOGSEVERITY_INFO(2),
		LOGSEVERITY_WARNING(3),
		LOGSEVERITY_ERROR(4),
		LOGSEVERITY_DISABLE(99);
		
		public int getValue() {
			return value;
		}
		
		private LogSeverity(int value) {
			this.value = value;
		}
		
		private int value;
	}
	
	String tabname;
	boolean tncascade;
	
	boolean rightButtonAllowed, rbcascade;
	
	HashMap<String, String> cookies;
	String[] keys, values;
	
	
	/**
	 * Set to true if want to run Chromium' message loop in the separate thread.
	 * It is possible only on Windows. Other operating systems (Linux GTK, Mac Cocoa) 
	 * require Chroimum's message loop to be executed on the main application thread.
	 * Default value is true. The value is ignored on Linux and Mac. 
	 */
	boolean separateMessageLoop = true;
	
	/**
	 * The path to a separate executable that will be launched for sub-processes.
	 * By default the browser process executable is used. 
	 */
	String browserSubprocessPath;
	
	/**
	 * The fully qualified path for the resources directory. If this value is
	 * empty the cef.pak and/or devtools_resources.pak files must be located in
	 * the module directory on Windows/Linux or the app bundle Resources directory
	 * on Mac OS X.
	 */
	String resourcesDirPath;
	
	/**
	 * The fully qualified path for the locales directory. If this value is empty
	 * the locales directory must be located in the module directory. This value
	 * is ignored on Mac OS X where pack files are always loaded from the app
	 * bundle Resources directory.
	 */
	String localesDirPath;

	/**
	 * The location where cache data will be stored on disk. If empty then
	 * browsers will be created in "incognito mode" where in-memory caches are
	 * used for storage and no data is persisted to disk. HTML5 databases such as
	 * localStorage will only persist across sessions if a cache path is specified. 
	 */
	String cachePath;
	
	/**
	 * The location where user data such as spell checking dictionary files will
	 * be stored on disk. If empty then the default platform-specific user data
	 * directory will be used ("~/.cef_user_data" directory on Linux,
	 * "~/Library/Application Support/CEF/User Data" directory on Mac OS X,
	 * "Local Settings\Application Data\CEF\User Data" directory under the user
	 * profile directory on Windows).
	 */
	String userDataPath;
	
	/**
	 * The locale string that will be passed to WebKit. If empty the default
	 * locale of "en-US" will be used. This value is ignored on Linux where locale
	 * is determined using environment variable parsing with the precedence order:
	 * LANGUAGE, LC_ALL, LC_MESSAGES and LANG.
	 */
	String locale;
	
	/**
	 * Comma delimited ordered list of language codes without any whitespace that
	 * will be used in the "Accept-Language" HTTP header. If empty then "en-US,en" 
	 * will be used.
	 */
	String acceptLanguageList;
	
	/**
	 * The directory and file name to use for the debug log. If empty a default
	 * log file name and location will be used. On Windows and Linux a "debug.log"
	 * file will be written in the main executable directory. On Mac OS X a
	 * "~/Library/Logs/<app name>_debug.log" file will be written where <app name>
	 * is the name of the main app executable.
	 */
	String logFile;
	
	/**
	 * The log severity. Only messages of this severity level or higher will be
	 * logged. Values are:
	 *   0 = LOGSEVERITY_DEFAULT - Default logging (currently INFO logging)
	 *   1 = LOGSEVERITY_VERBOSE
	 *   2 = LOGSEVERITY_INFO
	 *   3 = LOGSEVERITY_WARNING
	 *   4 = LOGSEVERITY_ERROR
	 *  99 = LOGSEVERITY_DISABLE - Completely disable logging
	 */
	LogSeverity logSeverity;
	int logSeverityAsInt;
	
	/**
	 * Set to a value between 1024 and 65535 to enable remote debugging on the
	 * specified port. For example, if 8080 is specified the remote debugging URL
	 * will be http://localhost:8080. CEF can be remotely debugged from any CEF or
	 * Chrome browser window.
	 */
	int remoteDebuggingPort;
	
	/**
	 * The number of stack trace frames to capture for uncaught exceptions.
	 * Specify a positive value to enable the CefRenderProcessHandler::OnUncaughtException() 
	 * callback. Specify 0 (default value) and OnUncaughtException() will not be called.
	 */
	int uncaughtExceptionStackSize;
	
	/**
	 * Set to true to disable the sandbox for sub-processes.
	 */
	boolean noSandbox;

	/**
	 * To persist session cookies (cookies without an expiry date or validity
	 * interval) by default when using the global cookie manager set this value to
	 * true. Session cookies are generally intended to be transient and most
	 * Web browsers do not persist them. A cachePath setting value must also be
	 * specified to enable this feature.
	 */
	boolean persistSessionCookies;
	
	/**
	 * To persist user preferences as a JSON file in the cache path directory 
	 * set this value to true. A cachePath setting value must also be specified
	 * to enable this feature. 
	 */
	boolean persistUserPreferences;
	
	/**
	 * Set to true to ignore errors related to invalid SSL certificates.
	 * Enabling this setting can lead to potential security vulnerabilities like
	 * "man in the middle" attacks. Applications that load content from the
	 * internet should not enable this setting. 
	 */
	boolean ignoreCertificateErrors;
	
	public ChromeSettings() {
		tabname = null;
		tncascade = false;
		rightButtonAllowed = true;
		rbcascade = false;
		cookies = new HashMap<String, String>();
	}
	
	/**
	 * Set tab name or use default web title.
	 * @param name If null is passed in, the tab name will return to default.
	 * @param cascade Indicates whether the tab name stays the same when a new tab opens from this tab.
	 * @return
	 */
	public ChromeSettings tabname(String name, boolean cascade) {
		this.tabname = name;
		this.tncascade = cascade;
		return this;
	}
	
	public ChromeSettings right_button(boolean rightButtonAllowed, boolean cascade) {
		this.rightButtonAllowed = rightButtonAllowed;
		this.rbcascade = cascade;
		return this;
	}
	
	/**
	 * Set or delete a cookie.
	 * @param key
	 * @param value If null is passed in, the cookie will be removed.
	 * @return
	 */
	public ChromeSettings cookie(String key, String value) {
		if (value == null) {
			if (cookies.containsKey(key))
				cookies.remove(key);
		}
		else
			cookies.put(key, value);
		return this;
	}
	
	/**
	 * Set cookies from cookies string.
	 * @param cookie_string
	 * @return
	 */
	public ChromeSettings cookie(String cookie_string) {
		String[] pairs = cookie_string.split("=(?=;)|; ?");
		for (int i = 0; i < pairs.length; i++) {
			String[] kv = pairs[i].split("=", 2);
			if (kv.length == 2)
				cookie(kv[0], kv[1]);
		}
		return this;
	}
	
	ChromeSettings Finalize() {
		keys = new String[cookies.size()];
		values = new String[cookies.size()];
		int i = 0;
		Iterator<Entry<String, String>> ci = cookies.entrySet().iterator();
		Entry<String, String> c;
		while (ci.hasNext()) {
			c = ci.next();
			keys[i] = c.getKey();
			values[i] = c.getValue();
			i++;
		}
		return this;
	}

	public boolean isSeparateMessageLoop() {
		return separateMessageLoop;
	}

	public void setSeparateMessageLoop(boolean separateMessageLoop) {
		this.separateMessageLoop = separateMessageLoop;
	}

	public boolean isRightButtonAllowed() {
		return rightButtonAllowed;
	}

	public void setRightButtonAllowed(boolean rightButtonAllowed) {
		this.rightButtonAllowed = rightButtonAllowed;
	}

	public boolean isNoSandbox() {
		return noSandbox;
	}

	public void setNoSandbox(boolean noSandbox) {
		this.noSandbox = noSandbox;
	}

	public String getBrowserSubprocessPath() {
		return browserSubprocessPath;
	}

	public void setBrowserSubprocessPath(String browserSubprocessPath) {
		this.browserSubprocessPath = browserSubprocessPath;
	}

	public String getResourcesDirPath() {
		return resourcesDirPath;
	}

	public void setResourcesDirPath(String resourcesDirPath) {
		this.resourcesDirPath = resourcesDirPath;
	}

	public String getLocalesDirPath() {
		return localesDirPath;
	}

	public void setLocalesDirPath(String localesDirPath) {
		this.localesDirPath = localesDirPath;
	}

	public String getCachePath() {
		return cachePath;
	}

	public void setCachePath(String cachePath) {
		this.cachePath = cachePath;
	}

	public String getUserDataPath() {
		return userDataPath;
	}

	public void setUserDataPath(String userDataPath) {
		this.userDataPath = userDataPath;
	}

	public boolean isPersistSessionCookies() {
		return persistSessionCookies;
	}

	public void setPersistSessionCookies(boolean persistSessionCookies) {
		this.persistSessionCookies = persistSessionCookies;
	}

	public boolean isPersistUserPreferences() {
		return persistUserPreferences;
	}

	public void setPersistUserPreferences(boolean persistUserPreferences) {
		this.persistUserPreferences = persistUserPreferences;
	}

	public String getLocale() {
		return locale;
	}

	public void setLocale(String locale) {
		this.locale = locale;
	}

	public String getAcceptLanguageList() {
		return acceptLanguageList;
	}

	public void setAcceptLanguageList(String acceptLanguageList) {
		this.acceptLanguageList = acceptLanguageList;
	}

	public String getLogFile() {
		return logFile;
	}

	public void setLogFile(String logFile) {
		this.logFile = logFile;
	}

	public LogSeverity getLogSeverity() {
		return logSeverity;
	}

	public void setLogSeverity(LogSeverity logSeverity) {
		this.logSeverity = logSeverity;
		this.logSeverityAsInt = this.logSeverity.getValue();
	}

	public int getRemoteDebuggingPort() {
		return remoteDebuggingPort;
	}

	public void setRemoteDebuggingPort(int remoteDebuggingPort) {
		this.remoteDebuggingPort = remoteDebuggingPort;
	}

	public int getUncaughtExceptionStackSize() {
		return uncaughtExceptionStackSize;
	}

	public void setUncaughtExceptionStackSize(int uncaughtExceptionStackSize) {
		this.uncaughtExceptionStackSize = uncaughtExceptionStackSize;
	}
	
}

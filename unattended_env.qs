function Controller() {
  gui.pageWidgetByObjectName("WelcomePage").completeChanged.connect(function() {
    gui.clickButton(buttons.NextButton);
  });

  installer.installationFinished.connect(function() {
    gui.clickButton(buttons.CommitButton);
  });
}

Controller.prototype.WelcomePageCallback = function() {
}

Controller.prototype.CredentialsPageCallback = function() {
  gui.clickButton(buttons.NextButton);
}

Controller.prototype.IntroductionPageCallback = function() {
  gui.clickButton(buttons.NextButton);
}

Controller.prototype.DynamicTelemetryPluginFormCallback = function() {
  var disableStatisticRadioButton = gui.findChild(gui.currentPageWidget(), "disableStatisticRadioButton");

  if (null != disableStatisticRadioButton) {
    disableStatisticRadioButton.checked = true;
  }

  gui.clickButton(buttons.NextButton);
}

Controller.prototype.TargetDirectoryPageCallback = function() {
  var QT_TARGET_DIR = installer.environmentVariable("QT_TARGET_DIR");

  gui.currentPageWidget().TargetDirectoryLineEdit.text = QT_TARGET_DIR;
  gui.clickButton(buttons.NextButton);
}

Controller.prototype.ComponentSelectionPageCallback = function() {
  var QT_VERSION = installer.environmentVariable("QT_VERSION");
  var QT_COMPONENTS = installer.environmentVariable("QT_COMPONENTS");

  var componentBaseName = "qt.qt5." + QT_VERSION.split(".").join("");
  removeNonEssentialDependencies(componentBaseName);
  installer.setValue("SDKToolBinary", "");

  var componentSelectionPage = gui.currentPageWidget();
  componentSelectionPage.deselectAll();

  QT_COMPONENTS.split(",").forEach(function(componentName) {
    var fullComponentName = componentBaseName + "." + componentName;
    removeNonEssentialDependencies(fullComponentName);
    componentSelectionPage.selectComponent(fullComponentName);
  });

  gui.clickButton(buttons.NextButton);
}

function removeNonEssentialDependencies(componentName) {
  var component = installer.componentByName(componentName);

  if (null != component) {
    var dependencies = component.dependencies.filter(function(dependency) {
      if (dependency.includes(".doc"))
        return false;

      if (dependency.includes(".examples"))
        return false;

      if ("qt.tools.qtcreator" === dependency)
        return false;

      return true;
    });

    component.setValue("Dependencies", dependencies.join());
  }
}

Controller.prototype.LicenseAgreementPageCallback = function() {
  gui.currentPageWidget().AcceptLicenseRadioButton.checked = true;
  gui.clickButton(buttons.NextButton);
}

Controller.prototype.StartMenuDirectoryPageCallback = function() {
  gui.clickButton(buttons.NextButton);
}

Controller.prototype.ReadyForInstallationPageCallback = function() {
  gui.clickButton(buttons.CommitButton);
}

Controller.prototype.PerformInstallationPageCallback = function() {
}

Controller.prototype.FinishedPageCallback = function() {
  var runItCheckBox = gui.findChild(gui.currentPageWidget(), "launchQtCreatorCheckBox");

  if (null != runItCheckBox) {
    runItCheckBox.checked = false;
  }

  gui.clickButton(buttons.FinishButton);
}

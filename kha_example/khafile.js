let project = new Project('Empty');

project.addSources('Sources');
project.addAssets('../Bundled/**'); // Make this OS specific..
project.addLibrary('../../Libraries/sunvox');

resolve(project);

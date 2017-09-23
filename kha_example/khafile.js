let project = new Project('Empty');

project.addSources('Sources');
project.addAssets('Assets/**'); // Make this OS specific..
project.addLibrary('../../Libraries/sunvox');

resolve(project);

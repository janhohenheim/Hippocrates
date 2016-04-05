# JNF_NEAT

My Implementation of Kenneth Stanley and Risto Miikkulainen's NEAT (NeuroEvolution
of Augmenting Topologies, http://nn.cs.utexas.edu/downloads/papers/stanley.ec02.pdf).

It focuses (in contrast to other implementations) on

- Speed - through modern and efficient C++14
- Clean Code - through constant ongoing refactoring and a deep care for aethetics
- Usability - through beeing able to be used without much knowledge of Neural Networks

# Usage
First, you have to instanciate a `NetworkTrainer`. This class will take care of everything. It uses standard training values if not provided with a parameter. If you know what you're doing, you can provide it with a `TrainingParameter` instance to tweak the learning process.

You then have to provide an implementation of the `ITrainable` interface 
// TODO jnf
// Continue README.md godammit

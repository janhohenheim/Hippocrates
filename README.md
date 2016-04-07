# JNF_NEAT

My implementation of Kenneth Stanley and Risto Miikkulainen's NEAT (NeuroEvolution
of Augmenting Topologies, http://nn.cs.utexas.edu/downloads/papers/stanley.ec02.pdf).

It focuses (in contrast to other implementations) on

- Speed - through modern and efficient C++14
- Clean Code - through constant ongoing refactoring and a deep care for aesthetics
- Usability - through being able to be used without much knowledge of Neural Networks

- Multi-platform - written on three different OS-systems (Windows, Ubuntu, MacOS X) and two different IDEs, it is safe to say, that it will work on multiple platforms, flawlessly.

##Foreword

TODO


##Usage
First, you have to instantiate a `NeuralNetworkTrainer`. This class will take care of everything. It uses standard training values if not provided with a parameter. If you know what you're doing, you can provide it with a `NeuralNetworkTrainer::RuleSet` instance to tweak the learning process.

You then have to provide an implementation of the `ITrainable` interface. It's methods are
- Update()
- GetOrCalculateFitness()
- ReceiveNetworkOutputs()
- ProvideNetworkWithInputs()

###Update()
This method gets called automatically multiple times during training.
> default updatesPerGeneration: 1  
> Imagine this value as **number of actions per lifetime**

The actions of your object should take place here. This almost always boils down to **executing the command the Neural Network decides to use**.  
(Remember: You get this Informtion by calling `LoadNeuralNetworkOutputs()`).

**Example**: Let's say you want to train an artificial player for Super Mario World. This method should then take care of actually pressing the buttons your network want you to. In this specific case, it should also update the whole game for a frame, so enemies and items can react to Mario.

###GetOrCalculateFitness()
This method tells the trainer how good this specific instance is compared to others.  
It gets called automatically when the `ITrainable` object dies 
> It's used to generate its offspring, with a fitness score of zero or lower meaning that the genes of this individualare not going to get passed on

> default minFitness: -2147483646  
> default maxFitness: 100

Note that in very analog programs such as real world simulations, true perfection should be unreachable

**Example**: A simulated chess player could have a fitness method implemented like this:
```
unsigned int ChessSim::GetOrCalculateFitness() {
  unsigned int fitness = 0;  
  for (const auto & piece : enemyKilledPieces) {
    fitness += piece.GetImportance();
  }
  for (const auto & piece : ownKilledPieces) {
    fitness -= piece.GetImportance();
  }
  return fitness;
}
```

###ReceiveNetworkOutputs()
This method returns the conclusions of your neural network as a series of floats
> default minNeuralCharge = 0.0;  
> default maxNeuralCharge = 1.0;  
> It is **highly** recommended to leave these values like this (see advanced FAQ for details)

You'll want to translate these values almost all the time into something your program can work with and store in a member.

**Example**: TODO

###ProvideNetworkWithInputs()
TODO
> default minNeuralCharge = 0.0;  
> default maxNeuralCharge = 1.0;  
> It is **highly** recommended to leave these values like this (see advanced FAQ for details)

**Example**: TODO

###Full Example
 
 TODO
 
## FAQ

TODO

## Advanced FAQ

TODO

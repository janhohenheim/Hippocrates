# JNF_NEAT

My implementation of Kenneth Stanley and Risto Miikkulainen's NEAT (NeuroEvolution
of Augmenting Topologies, http://nn.cs.utexas.edu/downloads/papers/stanley.ec02.pdf).

It focuses (in contrast to other implementations) on

- Speed - through modern and efficient C++14
- Clean Code - through constant ongoing refactoring and a deep care for aesthetics
- Usability - through beeing able to be used without much knowledge of Neural Networks

##Foreword

###Motivation
One of the problems of machine learning is its steep learning curve. If you want to let your code learn,
you've got few choices: Use expensive proprietary modules or use libraries that are aimed at people with experience in AI.
If you want to learn how machine learning works, you've got to read scientific papers with tons of buzzwords.
The provided code is often made by people who are brilliant at researching, but have only got poor programming skills.

We think this is a shame. A programmer shouldn't have to learn about the internals of a class.
He should be able to use it intuitively, in a matter that it relieves him from work, not set him up for more.
That's the age old principle of encapsulation!

Another problem we've encountered, was platform dependency. Despite being conceived as a platform independent language,
we encountered various implementations of NEAT, that managed to break this. Examples included code with for loops looking like this:
```sh
for( i = 0; i < 10; i++ ){
    ...
}
```
Notice the `i` not having been declared? Some compilers permit this. Another, more subtle one was the `abstract` keyword
of Microsoft Visual Studio. It's actually not part of the language. The official way is to write an (admittedly more arbitrary) `= 0`
at the end of a function.

###What is NEAT?

TODO

##Usage
First, you have to instantiate a `NeuralNetworkTrainer`. This class will take care of everything. It uses standard training values if not provided with a parameter.
If you know what you're doing, you can provide it with a `NeuralNetworkTrainer::RuleSet` instance to tweak the learning process.

You then have to provide an implementation of the `ITrainable` interface. It's methods are
- Update()
- GetOrCalculateFitness()
- ReceiveNetworkOutputs()
- ProvideNetworkWithInputs()

###Update()
This method gets called automatically multiple times during training.
> default updatesPerGeneration: 1
> Imagine this value as **number of actions per lifetime**

The actions of your object should take place here. This almost always boils down to **executing the command the Neural Network decides to use**. (Remember: You get this Information by calling `LoadNeuralNetworkOutputs()`).

**Example**: Say you want to train an artificial player for Super Mario World. This method should then take care of actually pressing the buttons your network want you to. In this specific case, it should also update the whole game for a frame, so enemies and items can react to Mario.

###GetOrCalculateFitness()
This method tells the trainer how good this specific instance is compared to others.
It gets called automatically when the `ITrainable` object dies
> It's used to generate this objects offspring, with a fitness score of zero or lower meaning that this individuals genes are not going to get passed on

> default minFitness: -2147483646
> default maxFitness: 100

Note that in very analog programs such as real world simulations, true perfection should be unreachable

**Example**: A simulated chess player could have a fitness method implemented like this:
```sh
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

Almost always you'll want to translate these values into something your program can work with and store in a member

**Example**: TODO

###ProvideNetworkWithInputs()
This method describes what your network "sees". It get's called automatically whenever your network needs updated real world knowledge.
Remember that it works (just like `ReceiveNetworkOutputs()`) with a vector of doubles, so most of the time you'll want to translate your
inputs by dividing them by their maximally possible values.
> default minNeuralCharge = 0.0;  
> default maxNeuralCharge = 1.0;  
> It is **highly** recommended to leave these values like this (see advanced FAQ for details)

**Example**: Let's assume you want to create a handwriting reader.
Your input would be a 20 pixels wide and 20 pixels high image of a hand drawn letter.
In order to feed the neural network with this information,
we'll create a vector with 20 * 20 = 400 inputs, each one having a value between 0.0 and 1.0 that represents this pixels blackness.
We can do this in a variety of ways. One of them would be to add the RGB values of the pixel up and divide them by
the maximum possible, 255+255+255 = 765. By this method, a bright red pixel(255,0,0) would be represented in our 400 element vector by
the number 255 / 765 = 0.3333.

###Full Example
 
 TODO
 
## FAQ

TODO

## Advanced FAQ

TODO

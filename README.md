# JNF_NEAT

My implementation of Kenneth Stanley and Risto Miikkulainen's NEAT (NeuroEvolution
of Augmenting Topologies, http://nn.cs.utexas.edu/downloads/papers/stanley.ec02.pdf).

It focuses (in contrast to other implementations) on

- Speed - through modern and efficient C++14
- Clean Code - through constant ongoing refactoring and a deep care for aesthetics
- Usability - through being able to be used without much knowledge of Neural Networks
- Platform Independency - written on three different operating systems (Windows, Ubuntu, MacOS X) and two different IDEs (Visual Studio 2015, CLion), it is safe to say that it will work on multiple platforms, flawlessly.

##Foreword

###Motivation
One of the problems of machine learning is its steep learning curve. If you want to let your code learn,
you've got few choices: Use expensive proprietary modules or use libraries that are aimed at people with experience in AI.
If you want to learn how machine learning works, you've got to read scientific papers with tons of buzzwords.
The provided code is often made by people who are brilliant at researching, but have only got poor programming skills.

We think this is a shame. A programmer shouldn't have to learn about the internals of a class.
He should be able to use it intuitively, in a matter that it relieves him from work, not set him up for more.
That's the age old principle of encapsulation!

Another problem we've encountered was platform dependency. Despite being conceived as a platform independent language,
we encountered various implementations of NEAT, that managed to break this. Examples included code with for loops looking like this:
```
for( i = 0; i < 10; i++ ){  
    ...
}
```
Notice the `i` not having been declared? Some compilers permit this. Another more subtle one was the `abstract` keyword
from Microsoft Visual Studio. It's actually not part of the language. The official way is to write an (admittedly more arbitrary) `= 0`
at the end of a function.

###What is NEAT?

N/A

##Usage  
You first have to provide an implementation of the `IBody` interface. You need to provide a copy constructor as well as following methods:   
- Update()  
- GetFitness()  
- Reset  
- ProvideNetworkWithInputs()  

They are all explained in detail below.  
<details>
<summary>Example</summary>
N/A
</details>

You need to instantiate a `NeuralNetworkTrainer::TrainingParameters` object. You **have** to set its `numberOfInputs`, `numberOfOutputs`, `updatesPerGeneration` members.  
If you know what you're doing, you can change the members in the `advanced` structure to tweak the learning process.  

<details>
<summary>Example</summary>  
```
TrainingParameters params;
params.numberOfInputs = 2;
params.numberOfOutputs = 1;
params.updatesPerGeneration = 4;
```  
</details>


Then, you'll want to create a `NeuralNetworkTrainer` instance with our `TrainingParameters`.
<details>
<summary>Example</summary>
N/A
</details>

## Explanation of IBody
### Update()
This method gets called automatically multiple times during training.

The actions of your object should take place here. This almost always boils down to **executing the command the Neural Network decides to use**. This information is delivered to you by the parameter `const std::vector<float>& networkOutputs`.
<details>
<summary>Example</summary>
Say you want to train an artificial player for Super Mario World. This method should then take care of actually pressing the buttons your network wants you to. In this specific case, it should also update the whole game for a frame, so enemies and items can react to Mario. A possible interpretention (interpretation?) of the `networkOutputs` would be to say that every float in the vector is a button and should be pressed if it's value is above `0.5`.
</details>
### GetFitness()
This method tells the trainer how good this specific instance is compared to others.
It gets called automatically when the `INetworkTrainer` object dies.
It's used to generate this objects offspring with a fitness score of zero or lower, meaning that this individual's genes are not going to get passed on.

Note that in very analog programs such as real world simulations, true perfection should be unreachable.
<details>
<summary>Example</summary>
A simulated chess player could have a fitness method implemented like this:
```sh
int ChessSim::GetFitness() const {
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
or, if you store a member `fitness` that you change in the Update() function:
```sh
int ChessSim::GetFitness() const {
    return fitness
}
```
</details>
### Reset()
This method gets called after your training object has finished its lifecycle and starts to train again with different (or new) neural configurations. It should reset the training object to the state it had before the last (or the first/which training?) training.  

If you decide to use a member to store the `fitness`, it should be set to zero in here.

<details>
<summary>Example</summary>
 If you are programming a Super Mario World player, the code to restart the level should be in here.
</details>
### ProvideNetworkWithInputs()
This method describes what your network "sees". It gets called automatically whenever your network needs updated real world knowledge.
Remember that it works with a vector of floats, so most of the time you'll want to translate your inputs by dividing them by their biggest possible values.
<details>
<summary>Example</summary>
Let's assume you want to create a handwriting reader.
Your input would be a 20 pixels wide and 20 pixels high image of a hand drawn letter.
In order to feed the neural network with this information,
we'll create a vector with 20 * 20 = 400 inputs, each one having a value between 0.0 and 1.0 that represents this pixels blackness.
We can do this in a variety of ways.
One of them would be to add the RGB values of the pixel up and divide them by
the maximum possible, 255+255+255 = 765. By this method, a bright red pixel(255,0,0) would be represented in our 400 element vector by
the number 255 / 765 = 0.3333.
 </details>
 
## FAQ

N/A

## Design decisions

N/A

/*
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */


#include "EventObjects.h"

//#ifndef EventManger
//#define EventManger




//EventObjectScheduler WsSEventManger;
EventObjectScheduler WsSEventManger;
//#endif



void EventSchedulersISR(void){
	Serial.println("EventSchedulersISR");
	
	EventBaseObject * theNewObject = {0};
	voidFunctionWithEventBaseObjectParameter theNewFunc;
	
	
	//Serial.println(	theNewObject->testvalue());
	
	WsSEventManger.MyFIFO.getNextEvent(&theNewObject,theNewFunc);
	
	Serial.println(	theNewObject->testvalue());
	Serial.println("Fire");
	
	theNewFunc(theNewObject);
	Serial.println("Sent");
	
}


EventObjectScheduler::EventObjectScheduler(void)
{
	CustomFIFO MyFIFO;
	NVIC_ENABLE_IRQ(IRQ_SOFTWARE);
	attachInterruptVector(IRQ_NUMBER_t(IRQ_SOFTWARE ), EventSchedulersISR);
	NVIC_SET_PRIORITY(IRQ_SOFTWARE, 150);
}



void EventObjectScheduler::trigger(EventBaseObject * InfoObject, voidFunctionWithEventBaseObjectParameter useFunc){


	MyFIFO.addEvent(InfoObject,useFunc);
	
	
	
	NVIC_TRIGGER_IRQ(IRQ_SOFTWARE);
	
	
	
}


void CustomFIFO::addEvent(EventBaseObject * NewObject,voidFunctionWithEventBaseObjectParameter useFunc){
	MyObjects[addIndex]=NewObject;
	functionsToCall[addIndex]=useFunc;
	addIndex+=1;
	if (addIndex>=EventManger_CustomFIFO_length-1){addIndex=0;}
}


void  CustomFIFO::getNextEvent(EventBaseObject ** NewObject,voidFunctionWithEventBaseObjectParameter &useFunc){
	//EventBaseObject itemToReturn;
	*NewObject=MyObjects[retriveIndex];
	useFunc=functionsToCall[retriveIndex];
	retriveIndex+=1;
	if (retriveIndex>=EventManger_CustomFIFO_length-1){retriveIndex=0;}
	//return itemToReturn;
}




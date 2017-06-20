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


EventObjectScheduler::EventObjectScheduler(void)
{
	CustomFIFO MyFIFO;
}



void EventObjectScheduler::trigger(EventBaseObject InfoObject,voidFunctionWithEventBaseObjectParameter useFunc){
	MyFIFO.addEvent(InfoObject,useFunc);

}


void CustomFIFO::addEvent(EventBaseObject NewObject,voidFunctionWithEventBaseObjectParameter useFunc){
	MyObjects[addIndex]=NewObject;
	functionsToCall[addIndex]=useFunc;
	addIndex+=1;
	if (addIndex>EventManger_CustomFIFO_length){addIndex=0;}
}


EventBaseObject CustomFIFO::getNextEvent(void){
	EventBaseObject itemToReturn;
	itemToReturn=MyObjects[retriveIndex];
	retriveIndex+=1;
	if (retriveIndex>EventManger_CustomFIFO_length){retriveIndex=0;}
	return itemToReturn;
}




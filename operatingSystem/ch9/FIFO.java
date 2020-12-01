/**
 * This class implements the FIFO page-replacement strategy.
 *
 */

import java.util.LinkedList;
import java.util.Queue;

public class FIFO extends ReplacementAlgorithm
{
	// FIFO list of page frames
	private FIFOList frameList;

	/**
	 * @param pageFrameCount - the number of physical page frames
	 */
	public FIFO(int pageFrameCount) {
		super(pageFrameCount);
		frameList = new FIFOList(pageFrameCount);
	}

	/**
	 * insert a page into a page frame.
	 * @param pageNumber - the page number being inserted.
	 */
	public void insert(int pageNumber) {
		frameList.insert(pageNumber);
    }
		
	class FIFOList
	{
		Queue<Integer> que = new LinkedList<>();
		// the page frame list
		int[] pageFrameList;

		// the number of elements in the page frame list
		int elementCount;

		FIFOList(int pageFrameCount) {
			pageFrameList = new int[pageFrameCount];

            // we initialize each entry to -1 to indicate initial value is invalid 
            java.util.Arrays.fill(pageFrameList,-1);
			elementCount = 0;
		}

		/**
		 * @param pageNumber the number of the page to be 
		 *	inserted into the page frame list.
		 */
		void insert(int pageNumber) {
			//*
			System.out.println("\n=======================================================");
			//*/
			if(!search(pageNumber))
			{
				pageFaultCount++;
				//*
				System.out.print("Page " + pageNumber + " is not in the frame, ");
				//*/
				if(elementCount < pageFrameCount)
				{
					pageFrameList[elementCount] = pageNumber;
					System.out.println(
							que.offer(elementCount)
					)
					;

					elementCount++;
					//*
					System.out.println("have space, add page to pageFrameList[" + (elementCount - 1) + "].");
					System.out.println("PageFrameList: {");
					System.out.print("  ");
					dump();
					System.out.println("\n}");
					//*/
				} else {
					System.out.println(que.peek());
					pageFrameList[que.peek()] = pageNumber;
					//*
					System.out.println("no space, pop and push pageFrameList[" + que.peek() + "].");
					System.out.println("PageFrameList: {");
					System.out.print("  ");
					dump();
					System.out.println("\n}");
					//*/
					que.offer(que.poll());
				}
			}
			//*
			else {
				System.out.println("PageFrameList: {");
				System.out.print("  ");
				dump();
				System.out.println("\n}");
				System.out.println("Found page " + pageNumber + " at frameList[" + searchIndex(pageNumber) + "].");
			}
			//*/
        }

		// dump the page frames
		void dump() {
			for (int i = 0; i < pageFrameList.length; i++)
				System.out.print("["+i+"]"+pageFrameList[i]+", ");
		}


		/**
		 * Searches for page pageNumber in the page frame list
		 * @return true if pageNumber was found
		 * @return false if pageNumber was not found
		 */
		boolean search(int pageNumber) {
			boolean returnVal = false;

			for (int i = 0; i < pageFrameList.length; i++) {
				if (pageNumber == pageFrameList[i]) {
					returnVal = true;
					break;
				}
			}
			return returnVal;
		}

		// The following functions are only for illustration, should be commented in practice.

		/**
		 * Search for index of the page via pageNumber in pageFrameList, only for illustration.
		 * !!!Should only be used when the page is already in the frame!!!
		 * @param pageNumber
		 * @return an integer from 0 to pageFrameList.length
		 * @return -1 if not found
		 */
		int searchIndex(int pageNumber) {
			for(int i = 0; i < pageFrameList.length; i++) {
				if(pageNumber == pageFrameList[i]) {
					return i;
				}
			}
			return -1;
		}
	}
}

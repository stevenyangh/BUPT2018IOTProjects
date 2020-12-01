/**
 * Test harness for LRU and FIFO page replacement algorithms
 *
 * Usage:
 *	java [-Ddebug] Test <reference string size> <number of page frames>
 */

public class Test
{
	public static void main(String[] args) {
        if (args.length != 2) {
            System.err.println("Usage: java Test <reference string size> <number of page frames>");
            System.exit(-1);
        }

		PageGenerator ref = new PageGenerator(Integer.parseInt(args[0]));

		int[] referenceString = ref.getReferenceString();

		/* Use either the FIFO or LRU algorithms */
		ReplacementAlgorithm fifo = new FIFO(Integer.parseInt(args[1]));
		ReplacementAlgorithm lru = new LRU(Integer.parseInt(args[1]));

		// output a message when inserting a page
		for (int j : referenceString) {
			System.out.println("inserting " + j);
			lru.insert(j);
		}

		// output a message when inserting a page
		for (int j : referenceString) {
			System.out.println("inserting " + j);
			fifo.insert(j);
		}

		// report the total number of page faults
		System.out.println("LRU faults = " + lru.getPageFaultCount());
		System.out.println("FIFO faults = " + fifo.getPageFaultCount());
	}
}

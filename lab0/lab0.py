from lab0_utilities import *
	
class Languages:
	def __init__(self):
		self.data_by_year = {} # dict to be modified

	def build_trees_from_file(self, file_object):
		'''
		Bespoke Method. Assigns file to dictionary boi.
		'''
		# OK
		activeYear = -1

		for line in file_object:

			data = line.strip("\n").split(",") # clean data down
			try:
				(year, language, count) = (int(data[0]), data[1], int(data[2]))
				# use try/catch to ignore first line and avoid use of less efficient if statements

				entry = LanguageStat(language, year, count)

				if year == activeYear:
					# append to entry if current year is already going
					
					self.data_by_year[activeYear].balanced_insert(Node(entry))
					
				else:
					# make new entry and switch to new year.
					activeYear = year

					self.data_by_year[activeYear] = BalancingTree(Node(entry))
			except:
				pass

		return self.data_by_year
			
	def query_by_name(self, language_name):
		result = {}

		for k in self.data_by_year:
			# for every year
			nodes = self.data_by_year[k].traversal()

			for n in nodes:
				if n.val.name == language_name:
					result[k] = n.val.count

		return result

	def query_by_count(self, threshold = 0):
		result = {}

		for k in self.data_by_year:
			# for every year
			result[k] = []

			nodes = self.data_by_year[k].traversal()

			for n in nodes:
				if n.val.count > threshold:
				# EXCEEDS ===> > threshold; NOT >=
					result[k].append(n.val.name)

		return result

class BalancingTree:

	def __init__(self, root_node):
		self.root = root_node
	
	def balanced_insert(self, node, curr = None):
		curr = curr if curr else self.root
		self.insert(node, curr)
		self.balance_tree(node)


	def insert(self, node, curr = None):
		'''
		DO NOT USE - USE balanced_insert
		'''
		curr = curr if curr else self.root
		# insert at correct location in BST
		if node._val < curr._val:
			if curr.left is not None:
				self.insert(node, curr.left)
			else:
				node.parent = curr
				curr.left = node
		else:
			if curr.right is not None:
				self.insert(node, curr.right)
			else:
				node.parent = curr
				curr.right = node
		return


	def balance_tree(self, node):
		'''
		Given an inserted node, ascend until bf for a node iS UNBALANCED or we reach root
		'''
		n = node

		while n is not None:
			# while not at root, keep going
			
			# recompute balance factor after normal insertion
			n.bf = self.find_balance_factor(n)

			if n.bf == 2:
				if n.right.bf == -1:
					# opposing signs; right rotate bottom and then left rotate top
					self.right_rotate(n.right)
				self.left_rotate(n)
			elif n.bf == -2:
				if n.left.bf == 1:
					self.left_rotate(n.left)
				self.right_rotate(n)

			n = n.parent # go next up

	def update_height(self, node):
		node.height = 1 + max(self.height(node.left), self.height(node.right))

	def height(self, node):
		return node.height if node else -1

	def left_rotate(self, z):
		y = z.right # declare new apex node
		y.parent = z.parent # connect apex's parent to OG's parent
		if y.parent is None:
			self.root = y # apex COULD be new root
		else:
			if y.parent.left is z:
				# if OG is connected to the left, remap THAT connection (complete step 1)
				y.parent.left = y
			elif y.parent.right is z:
				# vice-versa
				y.parent.right = y
		
		z.right = y.left # move apex's leftboard connection to right side of OG
		if z.right is not None:
			z.right.parent = z # update parent
		
		y.left = z # connect OG to apex left
		z.parent = y # update link
		self.update_height(z)
		self.update_height(y)
		z.bf = self.find_balance_factor(z)
		y.bf = self.find_balance_factor(y)


	def right_rotate(self, z):
		'''
		Bespoke method. Rotates Tree boi to right.
		'''
		# OK
		y = z.left # define new apex
		y.parent = z.parent # map link from apex to parent

		if y.parent is None:
			self.root = y # set to root if no parent exists
		else:
			# remap apex's parent's downward connection
			if y.parent.right is z:
				y.parent.right = y
			elif y.parent.left is z:
				y.parent.left = y

		z.left = y.right # move apex's rightboard connection to OG
		if z.left is not None:
			z.left.parent = z # update subsidiary link
		y.right = z # final switchover
		z.parent = y
		# update heights
		self.update_height(z)
		self.update_height(y)
		z.bf = self.find_balance_factor(z)
		y.bf = self.find_balance_factor(y)


	def find_balance_factor(self, node):
		'''
		Height of right subtree - height of left subtree
		'''
		# compute height of subtrees
		self.heightTraverse(node)
		return self.height(node.right) - self.height(node.left)


	def is_balanced(self):
		nodes = self.traversal()
		for n in nodes:
			if n.bf > 1 or n.bf < -1:
				# VIOLATION
				return False
		return True

	def traversal(self):
		'''
		Returns an in-order traversal of the tree as a list of nodes
		'''
		return self.in_order(self.root)

	def in_order(self, node):
		'''
		Helper for above function
		'''
		result = []

		if node is not None:
			result += self.in_order(node.left)
			result.append(node)
			result += self.in_order(node.right)
		return result

	def heightTraverse(self, node):
		'''
		Perform post-order traversal to find tree subheights
		'''
		if node is not None:
			self.heightTraverse(node.left)
			self.heightTraverse(node.right)
			self.update_height(node)

	def print_tree(self):
		'''
		Debugger
		'''
		queueboi = [self.root]
		output = ""
		while queueboi:
			popboi = queueboi.copy()
			queueboi.clear()
			for boi in popboi:
				output += "{}{}[{}] ".format(boi.val.name[0], boi.height, boi.bf)
				if boi.left:
					queueboi += [boi.left]
				if boi.right:
					queueboi += [boi.right]
			output += "\n"
		return output



